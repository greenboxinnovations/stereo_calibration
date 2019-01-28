#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <stdio.h>
#include <iostream>

// mkdir
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include <algorithm>

using namespace std;
using namespace cv;

int x = 0;



bool isInverted(std::vector<Point2f> &corners){

  // get direction
  float prev = 0.0;
  for (int j = 0; j < corners.size(); ++j){
    if(prev == 0){
      prev = corners.at(j).x; 
    }
    else{
      if(prev > corners.at(j).x){        
        return true;
      }
      else{
        return false;
      }
    }            
  }
  return false;
}


void printMultiVec(std::vector<std::vector<Point2f>> &vect){
  for (int i = 0; i < vect.size(); i++) { 
        for (int j = 0; j < vect[i].size(); j++) 
            cout << vect[i][j] << " "; 
        cout << endl; 
    }
}


void invertMultiVec(std::vector<std::vector<Point2f>> &vect){
  for (int i = 0; i < vect.size(); i++) { 
      std::reverse(vect[i].begin(), vect[i].end()); 
  }
  std::reverse(vect.begin(), vect.end()); 
}


void makeSingleVector(std::vector<std::vector<Point2f>> &vectMul, std::vector<Point2f> &vect){
  for (int i = 0; i < vectMul.size(); i++) { 
        for (int j = 0; j < vectMul[i].size(); j++){          
          vect.push_back(vectMul[i][j]);
        }        
    }
}

void makeChessVec(std::vector<std::vector<Point2f>> &tempChessVec, std::vector<Point2f> &corners){
  int i_count = 0;      
  int j_count = 0;
  for (int i = 0; i < corners.size(); ++i){
      

      if(j_count == 13){
        j_count = 0;
        i_count++;
      }

      tempChessVec[i_count][j_count] = corners.at(i);
      j_count++;
  }  
}




int main(int argc, char const *argv[])
{
  string imgs_directory;
  string extension;
  int im_width, im_height;

  im_width = 1920;
  im_height = 1080;

  if(argc < 1){
    cout << "usage:\n./read_single <img_dir+/>\nspace to click, enter to clear chessboard" << endl;
    return 0;
  }


  imgs_directory  = argv[1];  
  extension = "jpg";

  bool show_chessboard = false;


  struct stat st = {0};

  if (stat(imgs_directory.c_str(), &st) == -1) {
      mkdir(imgs_directory.c_str(), 0700);
  }


  const string WINDOW_NAME1 = "left";  
  namedWindow(WINDOW_NAME1, WINDOW_NORMAL);  
  resizeWindow(WINDOW_NAME1, 640, 480);  


  const string WINDOW_NAME2 = "right";  
  namedWindow(WINDOW_NAME2, WINDOW_NORMAL);  
  resizeWindow(WINDOW_NAME2, 640, 480);  



  const string CHESSWINDOW1 = "left_chessboard";
  const string CHESSWINDOW2 = "right_chessboard";
  bool board_found1 = false;
  bool board_found2 = false;



  // get ip from file
  FileStorage fs("stereo_ip.yml", FileStorage::READ);
  string ip_left, ip_right;
  fs["ip_left"] >> ip_left;
  fs["ip_right"] >> ip_right;
  const string LEFT_IP = ip_left;
  const string RIGHT_IP = ip_right;

  VideoCapture cap1(LEFT_IP);
  VideoCapture cap2(RIGHT_IP);

  Mat img1, img_res1, img2, img_res2;
  Mat img_chess1, img_chess2;


  while (1) {
    cap1 >> img1;
    cap2 >> img2;

    resize(img1, img_res1, Size(im_width, im_height));    
    imshow(WINDOW_NAME1, img_res1); 


    resize(img2, img_res2, Size(im_width, im_height));    
    imshow(WINDOW_NAME2, img_res2);    



    switch(waitKey(30)) {

      // escape
      case 27:
        if(!show_chessboard){
          return 0;  
        }        
        break;


      // space
      case 32:
        if(!show_chessboard){
          show_chessboard = true;
          cout << "space"<< endl;

          
          cv::cvtColor(img_res1, img_chess1, COLOR_BGR2GRAY);
          cv::cvtColor(img_res2, img_chess2, COLOR_BGR2GRAY);




          namedWindow(CHESSWINDOW1, 0);
          resizeWindow(CHESSWINDOW1, 1280, 960);

          namedWindow(CHESSWINDOW2, 0);
          resizeWindow(CHESSWINDOW2, 1280, 960);

          vector<Point2f> corners1;
          vector<Point2f> corners2;
          Size boardSize = Size(13,9);
          Mat img_chess_bgr1;
          Mat img_chess_bgr2;
          
          board_found1 = findChessboardCorners(img_chess1, boardSize, corners1,
                    CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

          board_found2 = findChessboardCorners(img_chess2, boardSize, corners2,
                    CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

          
          cvtColor(img_chess1, img_chess_bgr1, COLOR_GRAY2BGR);
          cvtColor(img_chess2, img_chess_bgr2, COLOR_GRAY2BGR);
          drawChessboardCorners(img_chess_bgr1, boardSize, corners1, board_found1);
          drawChessboardCorners(img_chess_bgr2, boardSize, corners2, board_found2);


          if(isInverted(corners1)){
            cout << "corners1 is inverted" << endl;
          }
          if(isInverted(corners2)){
            cout << "corners2 is inverted" << endl; 
          }
          // for (int i = 0; i < corners1.size(); ++i){
          //   cout << corners1.at(i) << endl;
          // }

          // cout << "\n\n" << endl;

          // for (int j = 0; j < corners2.size(); ++j){
          //   cout << corners2.at(j) << endl;
          // }

          int cols = 13;
          int rows = 9;
          // Create
          vector< vector<Point2f> > tempChessVec(rows, vector<Point2f>(cols));

          printMultiVec(tempChessVec);

  


          printMultiVec(tempChessVec);
          invertMultiVec(tempChessVec);
          cout << "\n\n\n" << endl;
          printMultiVec(tempChessVec);

          vector<Point2f> corners2_new;

          makeSingleVector(tempChessVec, corners2_new);

          // for (int j = 0; j < row1.size(); ++j){
          //   cout << row1.at(j) << endl;
          // }      

          // cout << "\n\n" <<endl;

          // std::reverse(row1.begin(), row1.end());


          // for (int j = 0; j < row1.size(); ++j){
          //   cout << row1.at(j) << endl;
          // }  

          
          drawChessboardCorners(img_chess_bgr2, boardSize, corners2_new, board_found2);


          putText(img_chess_bgr1, "Y=confirm. N=discard", Point2f(30,30), FONT_HERSHEY_PLAIN, 2,  Scalar(0,0,255,255), 2);
          putText(img_chess_bgr2, "Y=confirm. N=discard", Point2f(30,30), FONT_HERSHEY_PLAIN, 2,  Scalar(0,0,255,255), 2);
          imshow(CHESSWINDOW1, img_chess_bgr1);
          imshow(CHESSWINDOW2, img_chess_bgr2);
        }        
        break;


      // y 
      case 121:

        if(show_chessboard){

          show_chessboard = false;
          board_found1 = false;
          board_found2 = false;
          destroyWindow(CHESSWINDOW1);
          destroyWindow(CHESSWINDOW2);


          x++;
          char filename1[200], filename2[200];          
          sprintf(filename1, "%s%dl.%s", imgs_directory.c_str(), x, extension.c_str());            
          sprintf(filename2, "%s%dr.%s", imgs_directory.c_str(), x, extension.c_str());
          
          cout << "Saving img pair " << x << endl;
          imwrite(filename1, img_res1);
          imwrite(filename2, img_res2);
        }
        break;

      // n 
      case 110:
        if(show_chessboard){

            show_chessboard = false;
            board_found1 = false;
            board_found2 = false;
            destroyWindow(CHESSWINDOW1);
            destroyWindow(CHESSWINDOW2);
        }
        break;

    }
  }
  return 0;
}
