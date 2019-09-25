/*
 * gog.cpp
 *
 *  Created on: 2017-5-10
 *      Author: di
 */

#include "gog.h"
#include "pixelfeatures.h"
#include "mcorr.h"
#include <math.h>
#include <algorithm>
#include <vector>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include <opencv2/core/eigen.hpp>

#include <iostream>
#define PI 3.141592

cv::Mat GOG::getFeature(cv::Mat image){

	  cv::Mat rimage,rimage_32f;
	  cv::resize(image,rimage,this->s);
	  rimage.convertTo(rimage_32f,CV_32F);

	  Pixelfeatures pixeleatures(param.lfparam);
	  cv::Mat F=pixeleatures.get_pixelfeatures(rimage_32f);


	  cv::Mat M1=patchGaussian(F);

	  cv::Mat M2=regionGaussian(M1);

	  return M2;
}

cv::Mat GOG::regionGaussian(cv::Mat F){
	cv::Mat weightmap;
	cv::Mat featureAll;

	if(!this->param.ifweight){
		weightmap=cv::Mat::zeros(F.size[0],F.size[1],CV_32F);
	}
	else{
		float sigma=F.size[1]/4.f;
		float  mu=F.size[1]/2.f;
		for(int i=1;i<F.size[1]+1;++i){
			cv::Mat weightmapcol(1,F.size[0],CV_32F,cv::Scalar::all( exp(-(i-mu)*(i-mu)/(2*sigma*sigma))/(sigma*sqrt(2*PI)) ));
			weightmap.push_back(weightmapcol);
		}
		weightmap=weightmap.t();
	}

	if(param.G==7){
		this->parGrid.gheight=F.size[0]/2;
		this->parGrid.gwidth=F.size[1];
		this->parGrid.ystep=parGrid.gheight/2;
		this->parGrid.xstep=parGrid.gwidth;
	}

	int gheight2 = this->parGrid.gheight/this->param.p;
	int gwidth2 = this->parGrid.gwidth;
	int ystep2 = this->parGrid.ystep/this->param.p;
	int xstep2 = this->parGrid.xstep;

	const int region_size[3]={gheight2,gwidth2,F.size[2]};
	cv::Mat region(3,region_size,CV_32F);
	for(int prow=0;prow<=F.size[0]-gheight2;prow=prow+ystep2){
		for(int pcol=0;pcol<=F.size[1]-gwidth2;pcol=pcol+xstep2){

			for(int i=0;i<region_size[0];++i){
				for(int j=0;j<region_size[1];++j){
					for(int k=0;k<region_size[2];++k){
						region.at<float>(i,j,k)=F.at<float>(i+prow,j+pcol,k);
					}
				}
			}

			cv::Mat regionFeature=GOG::gog(region,weightmap(cv::Rect(pcol,prow,gwidth2,gheight2)));
			featureAll.push_back(regionFeature);
		}
	}

	return featureAll;
}

cv::Mat GOG::patchGaussian(cv::Mat F){


	CreateCorr<4> Corr(F);
	const int dim_array_out_inter[3]={F.size[0],F.size[1],F.size[2]*(F.size[2]+1)/2};
	cv::Mat FCorr(3,dim_array_out_inter,CV_32F,cv::Scalar::all(0.f));
	Corr.getCorr(FCorr);


	const int F_dim_array_out_corrih[3]={F.size[0]+1,F.size[1]+1,F.size[2]};
	cv::Mat IH_F(3,F_dim_array_out_corrih,CV_32F,cv::Scalar::all(0.f));
	Corr.getCorrIH(IH_F);

	CreateCorr<4> CorrIH(FCorr);
	const int dim_array_out_corrih[3]={FCorr.size[0]+1,FCorr.size[1]+1,FCorr.size[2]};
	cv::Mat IH_Corr(3,dim_array_out_corrih,CV_32F,cv::Scalar::all(0.f));
	CorrIH.getCorrIH(IH_Corr);

	int halfSize=(param.k-1)/2;

	std::vector<int> col(F.size[0]/param.p*F.size[1]/param.p);
	std::vector<int> row(F.size[0]/param.p*F.size[1]/param.p);

	//init row
	auto iterRow=row.begin();
	for(int i=0;i<F.size[0];i=i+param.p){
		std::fill(iterRow,iterRow+F.size[1]/param.p,i);
		iterRow=iterRow+F.size[1]/param.p;
	}

	//init col
	for(int i=0,count=0;i<F.size[1];i=i+param.p,++count){
		col[count]=i;
	}
	for(int i=1;i<F.size[0]/param.p;++i){
		std::copy(col.begin(),col.begin()+F.size[1]/param.p,col.begin()+i*F.size[1]/param.p);
	}

	/*//test col
	for(int i=0;i<col.size();++i){
		std::cout<<i<<":"<<std::max(row[i]-halfSize+1,1)<<" ";
	}
	std::cout<<std::endl;
	//test row
	for(int i=0;i<row.size();++i){
		std::cout<<i<<":"<<std::min(row[i]+halfSize+1,IH_Corr.size[0]-1)<<" ";
	}
	std::cout<<std::endl;*/

	//
	cv::Mat F2;

	for(int i=0;i<col.size();++i){

		int xLeft=std::max(col[i]-halfSize+1,1);
		int xRight=std::min(col[i]+halfSize+1,IH_Corr.size[1]-1);
		int yUp=std::max(row[i]-halfSize+1,1);
		int yDown=std::min(row[i]+halfSize+1,IH_Corr.size[0]-1);

		cv::Mat sumFCorr=cv::Mat::zeros(1,IH_Corr.size[2],CV_32F);
		for(int ii=0;ii<IH_Corr.size[2];++ii){
			sumFCorr.at<float>(0,ii)=IH_Corr.at<float>(yDown,xRight,ii)+IH_Corr.at<float>(yUp-1,xLeft-1,ii)-IH_Corr.at<float>(yUp-1,xRight,ii)-IH_Corr.at<float>(yDown,xLeft-1,ii);
		}
		//test sumFCorr
		//std::cout<<sumFCorr<<std::endl;

		cv::Mat sumF=cv::Mat::zeros(1,IH_F.size[2],CV_32F);
		for(int ii=0;ii<IH_F.size[2];++ii){
			sumF.at<float>(0,ii)=IH_F.at<float>(yDown,xRight,ii)+IH_F.at<float>(yUp-1,xLeft-1,ii)-IH_F.at<float>(yUp-1,xRight,ii)-IH_F.at<float>(yDown,xLeft-1,ii);
		}
		//test sumF
		//std::cout<<sumF<<std::endl;


		int sumPixel=(xRight-xLeft+1)*(yDown-yUp+1);

		//test vec2Mat(sumFCorr,param.lfparam.num_element)
		//std::cout<<vec2Mat(sumFCorr,param.lfparam.num_element)<<std::endl;
		//test sumF.t()*sumF
		//std::cout<<sumF.t()*sumF<<std::endl;
		//test vec2Mat(sumFCorr,param.lfparam.num_element)-sumF.t()*sumF/sumPixel
		//std::cout<<vec2Mat(sumFCorr,param.lfparam.num_element)-sumF.t()*sumF/sumPixel<<std::endl;

		cv::Mat S=(vec2Mat(sumFCorr,param.lfparam.num_element)-sumF.t()*sumF/sumPixel)/(sumPixel-1);

		//double test3=cv::trace(S)[0];

		S=S+cv::Mat::eye(S.rows,S.cols,CV_32F)*param.espsilon0*std::max(cv::trace(S)[0],0.01);
		//test S
		//std::cout<<S<<std::endl;

		cv::Mat meanVec=sumF*(double)(1/sumPixel);
		//test mean
		//std::cout<<meanVec<<std::endl;

		cv::Mat keyMatrix;
		cv::hconcat(S+meanVec.t()*meanVec,meanVec.t(),keyMatrix);
		cv::Mat temp=meanVec.t();
		temp.push_back(1.f);
        temp = temp.t();
		keyMatrix.push_back(temp);
		//test keyMatrix
		//std::cout<<keyMatrix<<std::endl;

		//std::cout<<i<<" "<<cv::determinant(S)<<std::endl;

		if(std::abs(cv::determinant(S))>0){
			keyMatrix=keyMatrix*(pow(std::abs(cv::determinant(S)) ,-1.f/(S.rows+1)));
			//double test=cv::determinant(S);
			//double testtest=pow(abs(cv::determinant(S)),-1.f/(S.rows+1));
			/*//test keyMatrix
			std::cout<<i<<" ";
			for(int t=0;t<keyMatrix.cols;++t){
				std::cout<<keyMatrix.at<float>(0,t)<<" ";
			}
			std::cout<<std::endl;*/
			//test keyMatrix
			//std::cout<<keyMatrix<<std::endl;

			Eigen::Matrix<float,-1,-1> logm;
			cv::cv2eigen(keyMatrix,logm);
			logm=logm.log();
			cv::eigen2cv(logm,keyMatrix);
		}
		else{
			keyMatrix=0*keyMatrix;
		}

		keyMatrix=halfVec(keyMatrix);
		//test keyMatrix
		//std::cout<<keyMatrix<<std::endl;

		F2.push_back(keyMatrix);

	}

	const int reshapedDim[3]={F.size[0]/param.p,F.size[1]/param.p,F2.cols};
	cv::Mat reshapedM(3,reshapedDim,CV_32F,F2.data);

	/*for(int i1=0;i1<reshapedDim[0];++i1){
		std::cout<<std::endl;
		for(int i2=0;i2<reshapedDim[1];++i2){
			std::cout<<reshapedM.at<float>(i1,i2,0)<<" ";
		}
	}*/

	return reshapedM.clone();
}

cv::Mat GOG::vec2Mat(cv::Mat vecMat,int dim){
	cv::Mat OUT=cv::Mat::zeros(dim,dim,CV_32F);
	int ind=0;
    for(int r=0;r<dim;r++){
		for(int c=r;c<dim;c++){
		 OUT.at<float>(r,c) = vecMat.at<float>(0,ind);
		 OUT.at<float>(c,r) = vecMat.at<float>(0,ind);
		 ++ind;
		}
    }
    return OUT;
};

cv::Mat GOG::halfVec(cv::Mat fullMat){
	cv::Mat halfVec=cv::Mat::zeros(1,fullMat.cols*(fullMat.cols+1)/2,CV_32F);
	int ind=0;
	for(int r=0;r<fullMat.rows;++r){
		halfVec.at<float>(0,ind)=fullMat.at<float>(r,r);
		++ind;
		for(int c=r+1;c<fullMat.cols;++c){
			halfVec.at<float>(0,ind)=sqrt(2)*fullMat.at<float>(r,c);
			++ind;
		}
	}
	return halfVec;
}

cv::Mat GOG::gog(cv::Mat F,cv::Mat weightmap){
	cv::Mat u=cv::Mat(F.size[2],1,CV_32F,cv::Scalar::all(0));
	cv::Mat fi=cv::Mat(F.size[2],1,CV_32F,cv::Scalar::all(0));

	for(int i=0;i<F.size[0];++i){
		for(int j=0;j<F.size[1];++j){
			for(int ii=0;ii<F.size[2];++ii){
				u.at<float>(ii,0)=u.at<float>(ii,0)+F.at<float>(i,j,ii)*weightmap.at<float>(i,j);
			}
		}
	}
	u=u.mul(1.f/cv::sum(weightmap)[0]);
	cv::Mat sumfi=cv::Mat(F.size[2],F.size[2],CV_32F,cv::Scalar::all(0));
	for(int i=0;i<F.size[0];++i){
		for(int j=0;j<F.size[1];++j){
			for(int ii=0;ii<F.size[2];++ii){
				fi.at<float>(ii,0)=F.at<float>(i,j,ii);
			}
			cv::Mat temp;
			cv::mulTransposed(fi,temp,false,u);
			sumfi=sumfi+temp.mul(weightmap.at<float>(i,j));
		}
	}

	sumfi=sumfi.mul(1.f/cv::sum(weightmap)[0]);
	sumfi=sumfi+param.espsilon0*std::max(0.01,cv::trace(sumfi)[0])*cv::Mat::eye(sumfi.rows,sumfi.cols,CV_32F);

	cv::Mat keyMatrix;
	cv::hconcat(sumfi+u*u.t(),u,keyMatrix);
	cv::Mat lastrow=u.clone();
	lastrow.push_back(1.f);
    lastrow = lastrow.t();
	keyMatrix.push_back(lastrow);
	keyMatrix=keyMatrix.mul(pow(cv::determinant(sumfi),-1.f/(sumfi.rows+1)));



	// logm
	Eigen::Matrix<float,-1,-1> eigMat;
	cv::cv2eigen(keyMatrix,eigMat);
	Eigen::Matrix<float,-1,-1> logm;
	logm=eigMat.log();
	cv::eigen2cv(logm,keyMatrix);


	std::vector<float> toStraight;
	for(int i=0;i<keyMatrix.rows;++i){
		toStraight.push_back(keyMatrix.at<float>(i,i));
		for(int j=i+1;j<keyMatrix.cols;++j){
			toStraight.push_back(sqrt(2.f)*keyMatrix.at<float>(i,j));
		}
	}

	cv::Mat Feature(toStraight,1);

	return Feature;
}


