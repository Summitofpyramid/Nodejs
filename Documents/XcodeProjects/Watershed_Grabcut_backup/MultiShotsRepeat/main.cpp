
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ocl/ocl.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/objdetect.hpp>


using namespace std;

int main(void) {
    
    string path = "/Users/JohnsonJohnson/Downloads/thesis_1/Figures/KLFDAdemo3.jpg";
    cv::Mat mat = cv::imread(path);
    
    // show the image
    cv::namedWindow("Image", CV_WINDOW_AUTOSIZE);
    cv::moveWindow("Image", 0, 0);
    cv::imshow("Image", mat);
    
    cv::HOGDescriptor hog;
//    vector<float> descriptors;
//    hog.compute(mat, descriptors);
//    
    cout << "finished." << endl;
    cv::waitKey(0);
    cout << "bye." << endl;
    return EXIT_SUCCESS;
}



////
////  main.cpp
////  MultiShotsRepeat
////
////  Created by Dougalas Michael on 16/3/16.
////  Copyright © 2016年 Johnson. All rights reserved.
//
//#include "opencv2/opencv.hpp"
//#include <string>
//#include <iostream>
//#include <fstream>
//#include "watershed.h"
//#include "gauss.h"
//#include "descriptor.h"
//using namespace cv;
//using namespace std;
//
//void MyLine( Mat img, Point start, Point end )
//{
//    int thickness = 2;
//    int lineType = 8;
//    line( img,
//         start,
//         end,
//         Scalar( 0, 0, 255 ),
//         thickness,
//         lineType );
//}
//
//#define WATERSHED 1
//#define GRABCUT 0
//
//int main(int argc, char* argv[])
//{  ///Users/JohnsonJohnson/Documents/ReidDatasets/underground_reid/probes.txt
//    
//    fstream _file;
//    _file.open("/Users/JohnsonJohnson/Documents/ReidDatasets/prid_2011/multi_shot/cam_a/person_1.txt");
//    string imgName;
//    int count=0;
//    while((getline(_file,imgName))&&(count<1000))
//    {
//        
//        Mat image = cv::imread("/Users/JohnsonJohnson/Documents/ReidDatasets/prid_2011/multi_shot/cam_a/person_0001/"+imgName);
//        Mat image1;
//        
//        
//        //watershed method
//        if(WATERSHED)
//        {
//            cout<<"Segmenting images with (Watershed) method..."<<endl;
//            cvtColor(image, image1, CV_BGR2GRAY);
//            cv::Mat dest;
//            vector< vector<Point> > Contours;
//            vector< Vec4i > Hierachy;
//            cv::Mat blank(image.size(),CV_8U,cv::Scalar(50));
//            blank.convertTo(blank, CV_BGR2GRAY);
//            imshow("blank", blank);
//            
//            // Create markers image
//            cv::Mat markers(image.size(),CV_8U,cv::Scalar(0));
//            //Rect(topleftcornerX, topleftcornerY, width, height);
//            //top rectangle
//            markers(Rect(0,0,image.cols, 3)) = Scalar::all(1);
//            
//            //    //bottom rectangle
//            //    markers(Rect(0,image.rows-3,image.cols, 3)) = Scalar::all(1);
//            //    //left rectangle
//            //    markers(Rect(0,0,3,image.rows)) = Scalar::all(1);
//            //    //right rectangle
//            //    markers(Rect(image.cols-3,0,3,image.rows)) = Scalar::all(1);
//            //    //centre rectangle
//            //
//            //    int centreW = image.cols/2;
//            //    int centreH = image.rows/2;
//            //    markers(Rect(centreW-centreW/2,centreH-centreH/2, centreW, centreH)) = Scalar::all(120);
//            //    markers.convertTo(markers,CV_BGR2GRAY);
//            //    imshow("markers", markers);
//                //get the contour
//            Mat binary;
//            cvtColor(image, binary, CV_BGR2GRAY);
//            GaussianBlur(binary, binary, Size(7,7), 0);
//            imshow("binary", binary);
//            adaptiveThreshold(binary, binary, 150, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 0);
//            
//            findContours(binary, Contours,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//            
//            int cmin=50,cmax = 2000;
//            vector< vector<Point> >::const_iterator itc = Contours.begin();
//            while(itc!= Contours.end())
//            {
//                if(itc->size()<cmin||itc->size()>cmax)
//                    itc = Contours.erase(itc);
//                else
//                    ++itc;
//            
//            }
//            
//            drawContours(blank, Contours, -1, Scalar(0),1);
//          //  erode(blank, blank, Mat());
//          //  dilate(blank, blank, Mat());
//            imshow("contours",blank);
//            blank.convertTo(blank, CV_BGR2GRAY);
//            
//            //Create watershed segmentation object
//            WatershedSegmenter segmenter;
//            //    segmenter.setMarkers(markers);
//            //    cv::Mat wshedMask = segmenter.process(image);
//            //    cv::Mat mask;
//            //    convertScaleAbs(wshedMask, mask, 1, 0);
//            //
//            //    double thresh = threshold(mask, mask, 2,155, THRESH_BINARY);
//            //    bitwise_and(image, image, dest, mask);
//            Mat img,img_1;
//            
//            
//            cvtColor(image, img, CV_BGR2GRAY);
//            
//            GaussianBlur(img, img, Size(3,3),0);
//            // adaptiveThreshold(img, img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 0);
//            Mat n;
//            Laplacian(img, n, CV_8U);
//            //    imshow("lap",n);
//            
//            threshold(img, img_1, 100, 255, THRESH_BINARY);
//            
//            erode(img_1, img_1, Mat());
//            threshold(img_1,img_1, 1, 255, THRESH_BINARY_INV);
//            
//            img_1 = img_1+1;
//            imshow("img_1", img_1);
//            //  img_1.convertTo(img_1, CV_BGR2GRAY);
//            segmenter.setMarkers(img_1);
//            Mat Result = segmenter.process(image);
//            Mat mask2;
//            convertScaleAbs(Result, mask2,1,0);
//            Mat Dest;
//            double r = threshold(mask2, mask2,2,255,THRESH_BINARY);
//            //  imshow("mask2", mask2);
//            bitwise_and(image, image, Dest,mask2);
//            imshow("Result", Dest);
//            
//            
//            
//            dest.convertTo(dest,CV_8U);
//            
//            imshow("originalimage", image);
//            
//        
//            //    weightImg axisDraw;
//            //    axisDraw.HorizonAxis(image);
//            //    axisDraw.VerticalAxis(image);
//            //    axisDraw.DrawAxis(image);
//            
//        }
//        //---------------
//        
//        
//        // grubcut method
//        else
//        {
//            cout<<"Segmenting images with (Grabcut) method..."<<endl;
//            Mat1b mask_(image.rows,image.cols);
//            mask_.setTo(GC_PR_BGD);
//            int width = 0.05*image.cols;
//            int height = 0.4*image.rows;
//            Mat1b fg_seed0,fg_seed1,fg_seed2,fg_seed3,fg_seed4;
//            fg_seed0 = mask_(Range(image.rows/2-height,image.rows/2+height),
//                             Range(image.cols/2-width,image.cols/2+width));
//            
//            Point offset(10,10);
//            Point A(0,0),B(image.cols-10,0),C(0,image.rows-10),D(image.cols-10,image.rows-10);
//            fg_seed1 = mask_(Rect(A,A+offset));
//            fg_seed2 = mask_(Rect(B,B+offset));
//            fg_seed3 = mask_(Rect(C,C+offset));
//            fg_seed4 = mask_(Rect(D,D+offset));
//            fg_seed0.setTo(GC_FGD);
//            fg_seed1.setTo(GC_BGD);
//            fg_seed2.setTo(GC_BGD);
//            fg_seed3.setTo(GC_BGD);
//            fg_seed4.setTo(GC_BGD);
//            
//            Rect rectangle(1,1,image.cols,image.rows);
//            Mat bgModel,fgModel,result;
//            grabCut(image, mask_,rectangle,bgModel, fgModel,5,2);
//            
//            //  compare(result, cv::GC_PR_BGD, result, CMP_EQ);
//            //  Mat foreground(image.size(),CV_8UC3,Scalar(0,0,0));
//            //  result=result&1;
//            Mat1b fgpf = (mask_==GC_FGD)|(mask_==GC_PR_FGD);
//            Mat3b tmp = Mat3b::zeros(image.rows, image.cols);
//            image.copyTo(tmp, fgpf);
//            // image.copyTo(foreground,result);
//            imshow("foreground",tmp);
//            weightImg axisDraw;
//            axisDraw.HorizonAxis(tmp);
//            axisDraw.VerticalAxis(image);
//            axisDraw.DrawAxis(image);
//        }
//        
//        
//        ++count;
//        //choose to quit the program
//        
//        int c = waitKey(1000);
//        if (c=='\x1b')
//        {
//            destroyAllWindows();
//            return 0;
//        }
//        
//        
//        //-------------
//        
//        
//        
//    }
//    
//    
//    
//}
