/*
 * mcorr.h
 *
 *  Created on: 2017-6-11
 *      Author: di
 */

#ifndef MCORR_HPP_
#define MCORR_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <algorithm>
#include <vector>
#include <thread>



template<int threadnum> class CreateCorr{
public:
	cv::Mat F;
	int h,w,numchannel;

	CreateCorr(cv::Mat F){
		this->F=F;
		h=F.size[0];
		w=F.size[1];
		numchannel=F.size[2];

	}


unsigned creCorr(int th_id,cv::Mat Y){
	int starty,incy;
	starty=th_id;
	incy=threadnum;

	for(int y = starty; y<h; y = y + incy){
        for(int x = 0; x<w; x++){
            int ind = 0;
            for(int ch1 = 0; ch1<numchannel; ch1++){
                for(int ch2 = ch1; ch2<numchannel; ch2++){
                    Y.at<float>(y,x,ind) = F.at<float>(y,x,ch1)*F.at<float>(y,x,ch2);
                    ind++;
                }
            }
        }
    }

    return 0;
}

unsigned creIH(int th_id,cv::Mat IH){
	int startc,incc;
	startc=th_id;
	incc=threadnum;

	for(int ch = startc; ch< numchannel; ch = ch + incc){
	  // x = 0, y =0
	  IH.at<float>(1,1,ch)= F.at<float>(0,0,ch);


	  // y = 0
	  for(int x = 1; x<w; x++)
		  IH.at<float>(1,x+1,ch) = IH.at<float>(1,x,ch) + F.at<float>(0,x,ch);

	  for(int y = 1; y<h; y++){
		  IH.at<float>(y+1,1,ch)= IH.at<float>(y,1,ch) +  F.at<float>(y,0,ch); //x = 0
		  for(int x = 1; x <w; x++)
			  IH.at<float>(y+1,x+1,ch)=IH.at<float>(y+1,x,ch)+IH.at<float>(y,x+1,ch)+F.at<float>(y,x,ch)-IH.at<float>(y,x,ch);
	  }
	}

	return 0;
}

void getCorr(cv::Mat Y){
	std::thread thrd[threadnum];

	for(int t=0;t<threadnum;++t){
		thrd[t]=std::thread(&CreateCorr::creCorr,this,t,Y);
	}
	for(int t=0;t<threadnum;++t){
		thrd[t].join();
	}
	return;
}

void getCorrIH(cv::Mat IH){
	std::thread thrd[threadnum];

	for(int t=0;t<threadnum;++t){
		thrd[t]=std::thread(&CreateCorr::creIH,this,t,IH);
	}
	for(int t=0;t<threadnum;++t){
		thrd[t].join();
	}
	return;
}

};




#endif /* MCORR_HPP_ */
