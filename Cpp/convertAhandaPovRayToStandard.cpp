// This file converts the file format used at http://www.doc.ic.ac.uk/~ahanda/HighFrameRateTracking/downloads.html
// into the standard [R|T] world -> camera format used by OpenCV
// It is based on a file they provided there, but makes the world coordinate system right handed, with z up,
// x right, and y forward.

#include <opencv2/core.hpp>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace cv;
using namespace std;
Vec3f direction;
Vec3f upvector;
void convertAhandaPovRayToStandard(const char * filepath,
                                   int imageNumber,
                                   Mat& cameraMatrix,
                                   Mat& R,
                                   Mat& T)
{
    char text_file_name[600];
    sprintf(text_file_name,"%s/%04d.txt",filepath,imageNumber);

    cout << "text_file_name = " << text_file_name << endl;

    ifstream cam_pars_file(text_file_name);
    if(!cam_pars_file.is_open())
    {
        cerr<<"Failed to open param file, check location of sample trajectory!"<<endl;
        exit(1);
    }


    Mat M(4, 4, CV_64F);
    R=Mat(3,3,CV_64F);
    for (int i = 0; i < 16; i++) {
        double x;
        cam_pars_file >> x;
        M.at<double>(i) = x;
    }
    R = M(cv::Rect(0, 0, 3, 3));

    T = M(cv::Rect(3, 0, 1, 3));
   cout<<"T: "<<T<<endl<<"pos: "<<Mat(R)<<endl;
    cout<<"M: "<<M<<endl;
   /* cameraMatrix=(Mat_<double>(3,3) << 480,0.0,320.5,
										    0.0,480.0,240.5,
										    0.0,0.0,1.0);*/
    cameraMatrix=(Mat_<double>(3,3) << 566.3098,0.0,384.9639,
                  0.0,566.7987,297.9757,
                  0.0,0.0,1.0);

}



