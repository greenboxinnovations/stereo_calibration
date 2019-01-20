#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <stdio.h>
#include <iostream>

// mkdir
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


using namespace std;
using namespace cv;

int x = 0;

int main(int argc, char const *argv[])
{
 
  if(argc < 2){
    cout << "usage:\n./undistort_check <calib_file>" << endl;
    return 0;
  }


  const string WINDOW_NAME1 = "123";  
  namedWindow(WINDOW_NAME1, WINDOW_NORMAL);  
  resizeWindow(WINDOW_NAME1, 1280, 960);  

  string calib_file  = argv[1];
  
  

  // get ip from file
  FileStorage fsc("ip.yml", FileStorage::READ);
  string ip;
  fsc["ip"] >> ip;
  const string CAM_IP = ip;
  VideoCapture cap(CAM_IP);


  FileStorage fs(calib_file, FileStorage::READ);
  Mat K, D;
  fs["camera_matrix"] >> K;  
  fs["distortion_coefficients"] >> D;
    
  Mat img, u_img, display;
  bool show_rect = true;
  while (1) {
    cap >> img;


    if(!img.empty()){
      undistort(img, u_img, K, D);    
    }
    
    imshow(WINDOW_NAME1, display);
    if(show_rect){
      display = u_img;
    } else{
      display = img;
    }
    
    switch(waitKey(30)) {
      case 27:
        return 0;

      case 100:
        show_rect = !show_rect;
    }
  }
  return 0;
}
