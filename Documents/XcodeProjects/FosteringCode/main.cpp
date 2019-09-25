
#include "sift.hpp"
#include <fstream>
#include <iomanip>
#include<opencv2/core/core.hpp>
#include "ReidDescriptor.h"

using namespace std;
using namespace cv;

int main(){
    ReID test;
    string path("/Users/JohnsonJohnson/Documents/ReidDatasets/VIPeR/cam_a/000_45.bmp");
    Mat img = imread(path);
    vector<Mat> temp;
    cvtColor(img, img, CV_BGR2HSV);
    split(img, temp);
    FileStorage fs("hsv_img.yml",FileStorage::WRITE);

    Mat hist = test.getWhsvFeature(img);
    
        fs<<"hsv_img_h"<<temp[0];
        fs<<"hsv_img_s"<<temp[1];
        fs<<"hsv_img_v"<<temp[2];
    fs.release();
    }
