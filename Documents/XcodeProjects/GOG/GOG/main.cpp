/*
 * main.cpp
 *
 *  Created on: 2017-4-25
 *      Author: di
 */
/*
 * main.cpp
 *
 *  Created on: 2017-4-25
 *      Author: di
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "gog.h"
#include <iostream>
#include "ctime"

int main()
{
    cv::Mat image;
    //image = cv::imread( argv[1], 1 );
    image = cv::imread("/Users/JohnsonJohnson/Documents/Fun/thread_31372425_20171216141509_s_199003_h_1018px_w_720px139964fdaa.jpg");
    if(  !image.data )//argc != 2 ||
    {
        printf( "No image data \n" );
        return -1;
    }
//    clock_t t1 = clock();
//    // 1.initial param
//    Param param1;
//    static const bool temporary[] = {true,true,true,false,false,false};
//    memcpy(param1.lfparam.usebase, temporary, sizeof temporary);
//    param1.lfparam.num_element=8;
//    
//    PartGrid partGrid;
//    
//    // 2. Pixel Feature Extraction
//    GOG temp(param1,partGrid);
//    cv::Mat M2=temp.getFeature(image);
//    
////    for(int i=0;i<M2.rows;++i){
////        std::cout<<M2.at<float>(i,0)<<std::endl;
////    }
//    std::cout<<"Time cost to extract GOG for this single image is "<<(std::clock()-t1)/(double)CLOCKS_PER_SEC<<" seconds."<<std::endl;
//    
    
    cv::namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
    cv::imshow( "Display Image", image );
    
    cv::waitKey(0);
    
    return 0;
}

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include "gog.h"
//#include <iostream>
//#include "ctime"
//
//int main( int argc, char** argv )
//{
//  cv::Mat image;
//  //image = cv::imread( argv[1], 1 );
//  image = cv::imread("/Users/JohnsonJohnson/Documents/ReidDatasets/VIPeR/cam_a/000_45.bmp");
//  if(  !image.data )//argc != 2 ||
//    {
//      printf( "No image data \n" );
//      return -1;
//    }
//    clock_t t1 = clock();
//      // 1.initial param
//      Param param1;
//      static const bool temporary[] = {true,true,true,false,false,false};
//      memcpy(param1.lfparam.usebase, temporary, sizeof temporary);
//      param1.lfparam.num_element=8;
//
//    PartGrid partGrid;
//
//    // 2. Pixel Feature Extraction
//    GOG temp(param1,partGrid);
//    cv::Mat M2=temp.getFeature(image);
//
////    for(int i=0;i<M2.rows;++i){
////        std::cout<<M2.at<float>(i,0)<<std::endl;
////    }
//    std::cout<<"Time cost to extract GOG for this single image is "<<(std::clock()-t1)/(double)CLOCKS_PER_SEC<<" seconds."<<std::endl;
//
//
//  cv::namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
//  cv::imshow( "Display Image", image );
//
//  cv::waitKey(0);
//
//  return 0;
//}

