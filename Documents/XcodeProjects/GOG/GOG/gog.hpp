/*
 * gog.hpp
 *
 *  Created on: 2017-4-25
 *      Author: di
 */
#ifndef GOG_HPP_
#define GOG_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "pixelfeatures.h"
#include <math.h>
#include <algorithm>
#include <vector>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include <opencv2/core/eigen.hpp>
#include <iostream>

#define PI 3.141592

struct Param{
	lfParam lfparam;
	int p=2;
	int k=5;
	float espsilon0=0.001;
	bool ifweight=true;
	int G=7;
};

struct PartGrid{
	int gwidth;
	int gheight;
	int ystep;
	int xstep;
};

cv::Mat patchGaussian(cv::Mat F,Param param){

	std::vector<std::vector<std::vector<float> > > result;
	for(int prow=0;prow<F.size[0];prow=prow+param.p){
		std::vector<std::vector<float> > eachRow;
		for(int pcol=0;pcol<F.size[1];pcol=pcol+param.p){
			// for each patch
			cv::Mat u=cv::Mat(F.size[2],1,CV_32F,cv::Scalar::all(0));
			cv::Mat fi=cv::Mat(F.size[2],1,CV_32F,cv::Scalar::all(0));

			int pixNum=0;
			for(int i=std::max(prow-param.p,0);i<std::min(prow+param.k-param.p,F.size[0]);++i){
				for(int j=std::max(pcol-param.p,0);j<std::min(pcol+param.k-param.p,F.size[1]);++j){
					for(int ii=0;ii<F.size[2];++ii){
						u.at<float>(ii,0)=u.at<float>(ii,0)+F.at<float>(i,j,ii);
					}
					++pixNum;
				}
			}
			u=u.mul(1.f/pixNum);
			cv::Mat sumfi=cv::Mat(F.size[2],F.size[2],CV_32F,cv::Scalar::all(0));
			for(int i=std::max(prow-param.p,0);i<std::min(prow+param.k-param.p,F.size[0]);++i){
				for(int j=std::max(pcol-param.p,0);j<std::min(pcol+param.k-param.p,F.size[1]);++j){
					for(int ii=0;ii<F.size[2];++ii){
						fi.at<float>(ii,0)=F.at<float>(i,j,ii);
					}
					cv::Mat temp;
					cv::mulTransposed(fi,temp,false,u);
					sumfi=sumfi+temp;
				}
			}

			sumfi=sumfi.mul(1.f/(pixNum-1));
			sumfi=sumfi+param.espsilon0*std::max(0.01,cv::trace(sumfi)[0])*cv::Mat::eye(sumfi.rows,sumfi.cols,CV_32F);

			cv::Mat keyMatrix;
			cv::hconcat(sumfi+u*u.t(),u,keyMatrix);
			cv::Mat lastrow=u.clone();
			lastrow.push_back(1.f);
			keyMatrix.push_back(lastrow.t());
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
			eachRow.push_back(toStraight);
		}
		result.push_back(eachRow);
	}

	const int re_size[3]={result.size(),result[0].size(),result[0][0].size()};
	cv::Mat re(3,re_size,CV_32F,cv::Scalar::all(0));
	for(int i=0;i<re_size[0];++i){
		for(int j=0;j<re_size[1];++j){
			for(int k=0;k<re_size[2];++k){
				re.at<float>(i,j,k)=result[i][j][k];
			}
		}
	}
	return re;

}

cv::Mat gog(cv::Mat F,cv::Mat weightmap){

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
	/*//debug
	float test=cv::sum(weightmap)[0];

	for(int i=0;i<weightmap.rows;++i){
		std::cout<<std::endl;
		for(int j=0;j<weightmap.cols;++j){
			std::cout<<"we:"<<weightmap.at<float>(i,j)<<" ";
		}
	}

	for(int i=0;i<u.rows;++i){
		std::cout<<std::endl;
		for(int j=0;j<u.cols;++j){
			std::cout<<"u:"<<u.at<float>(i,j)<<" ";
		}
	}
	for(int i=0;i<sumfi.rows;++i){
		std::cout<<std::endl;
		for(int j=0;j<sumfi.cols;++j){
			std::cout<<"s:"<<sumfi.at<float>(i,j)<<" ";
		}
	}

	*///enddug

	sumfi=sumfi+0.001*std::max(0.01,cv::trace(sumfi)[0])*cv::Mat::eye(sumfi.rows,sumfi.cols,CV_32F);
	cv::Mat keyMatrix;
	cv::hconcat(sumfi+u*u.t(),u,keyMatrix);
	cv::Mat lastrow=u.clone();
	lastrow.push_back(1.f);
	keyMatrix.push_back(lastrow.t());
	keyMatrix=keyMatrix.mul(pow(cv::determinant(sumfi),-1.f/(sumfi.rows+1)));

	/*//debug
	for(int i=0;i<keyMatrix.rows;++i){
		std::cout<<std::endl;
		for(int j=0;j<keyMatrix.cols;++j){
			std::cout<<"k:"<<keyMatrix.at<float>(i,j)<<" ";
		}
	}
	*///enddebug

	// logm
	Eigen::Matrix<float,-1,-1> eigMat;
	cv::cv2eigen(keyMatrix,eigMat);
	Eigen::Matrix<float,-1,-1> logm;
	logm=eigMat.log();
	cv::eigen2cv(logm,keyMatrix);
	/*//debug
	for(int i=0;i<keyMatrix.rows;++i){
		std::cout<<std::endl;
		for(int j=0;j<keyMatrix.cols;++j){
			std::cout<<"kl:"<<keyMatrix.at<float>(i,j)<<" ";
		}
	}
	*///enddebug

	std::vector<float> toStraight;
	for(int i=0;i<keyMatrix.rows;++i){
		toStraight.push_back(keyMatrix.at<float>(i,i));
		//std::cout<<"kv:"<<keyMatrix.at<float>(i,i)<<std::endl;
		for(int j=i+1;j<keyMatrix.cols;++j){
			toStraight.push_back(sqrt(2.f)*keyMatrix.at<float>(i,j));
			//std::cout<<"kv:"<<sqrt(2.f)*keyMatrix.at<float>(i,j)<<std::endl;
		}
	}
	cv::Mat Feature(toStraight,1);

	return Feature;
}

cv::Mat regionGaussian(cv::Mat F,Param param,PartGrid parGrid){
	cv::Mat weightmap;
	cv::Mat featureAll;

	if(!param.ifweight){
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

	int gheight2 = parGrid.gheight/param.p;
	int gwidth2 = parGrid.gwidth/param.p;
	int ystep2 = parGrid.ystep/param.p;
	int xstep2 = parGrid.xstep/param.p;

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


			cv::Mat regionFeature=gog(region,weightmap(cv::Rect(pcol,prow,gwidth2,gheight2)));
			featureAll.push_back(regionFeature);
		}
	}

	return featureAll;
}

#endif /*GOG.HPP*/
