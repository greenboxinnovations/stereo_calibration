#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
// mkdir
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include <algorithm>

// fs module
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
// string replace
#include <boost/algorithm/string.hpp> // include Boost, a C++ library

using namespace std;
using namespace cv;

int x = 1;
int chess_rows = 9;
int chess_cols = 6;


void MyLine( Mat img, Point start, Point end )
{
	int thickness = 2;
	int lineType = 8;
	line( img,
		start,
		end,
		Scalar( 0, 255, 0 ),
		thickness,
		lineType );
}


int nextPhotoIndex(std::string folder){
	int max_int = 0;	
	int temp_int = 0;
	try {
		std::string path = "/home/greenbox-desktop/Desktop/desktop/stereo_calibration/stereo/"+folder;
		for (const auto & entry : fs::directory_iterator(path)){

			std::string path_string = entry.path().u8string();
			boost::replace_all(path_string, path, "");		
			boost::replace_all(path_string, ".jpg", "");
			boost::replace_all(path_string, "/", "");
			boost::replace_all(path_string, "l", "");
			boost::replace_all(path_string, "r", "");
			// std::cout << path_string << std::endl;
			temp_int = std::stoi(path_string);

			if(temp_int >= max_int){
				max_int = temp_int;
				max_int++;
			}			
		}
	}catch (...) {}

	if(max_int == 0){
		max_int = 1;
	}
	return max_int;
}


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


	  // if(j_count == 9){
		if(j_count == chess_rows){        
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

	if(argc < 2){
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
	cap1.set(cv::CAP_PROP_BUFFERSIZE, 1);
	cap2.set(cv::CAP_PROP_BUFFERSIZE, 1);

	Mat img1, img_res1, img2, img_res2;
	Mat img_chess1, img_chess2;


	while (1) {
		

		try{
			cap1 >> img1;
			cap2 >> img2;
			img_res1 = img1.clone();
			img_res2 = img2.clone();

			MyLine( img1, Point( 640, 0 ), Point( 640, im_height) );
			MyLine( img1, Point( 1280, 0), Point( 1280, im_height) );
			MyLine( img1, Point( 0, 360 ), Point( im_width, 360 ) );
			MyLine( img1, Point( 0, 720 ), Point( im_width, 720 ) );


			MyLine( img2, Point( 640, 0 ), Point( 640, im_height) );
			MyLine( img2, Point( 1280, 0), Point( 1280, im_height) );
			MyLine( img2, Point( 0, 360 ), Point( im_width, 360 ) );
			MyLine( img2, Point( 0, 720 ), Point( im_width, 720 ) );

			// resize(img1, img_res1, Size(im_width, im_height));
			// resize(img2, img_res2, Size(im_width, im_height));
		}catch (const std::exception& ex) {
			cout << ex.what() << endl;
		}
		
		imshow(WINDOW_NAME1, img1);
		imshow(WINDOW_NAME2, img2);



		switch(waitKey(5)) {

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
				// Size boardSize = Size(13,9);
				// Size boardSize = Size(9,6);
				Size boardSize = Size(chess_rows,chess_cols);
				Mat img_chess_bgr1;
				Mat img_chess_bgr2;

				board_found1 = findChessboardCorners(img_chess1, boardSize, corners1,
					CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

				board_found2 = findChessboardCorners(img_chess2, boardSize, corners2,
					CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);


				cvtColor(img_chess1, img_chess_bgr1, COLOR_GRAY2BGR);
				cvtColor(img_chess2, img_chess_bgr2, COLOR_GRAY2BGR);



				// int cols = 13;
				// int rows = 9;
				int cols = 9;
				int rows = 6;

				// int cols = chess_cols;
				// int rows = chess_rows;



				if(isInverted(corners1)){
					cout << "corners1 is inverted" << endl;
					try{
						vector< vector<Point2f> > tempChessVec1(rows, vector<Point2f>(cols));
						// cout << chess_rows << endl;
						// cout << chess_cols << endl;
						// vector< vector<Point2f> > tempChessVec1(chess_rows, vector<Point2f>(chess_cols));
						makeChessVec(tempChessVec1,corners1);
						invertMultiVec(tempChessVec1);
						vector<Point2f> corners1_new;
						makeSingleVector(tempChessVec1, corners1_new);
						drawChessboardCorners(img_chess_bgr1, boardSize, corners1_new, board_found1);
					}catch (const std::exception& ex) {
						cout << ex.what() << endl;						
					}
				}
				else{
					drawChessboardCorners(img_chess_bgr1, boardSize, corners1, board_found1);
				}

				if(isInverted(corners2)){
					cout << "corners2 is inverted" << endl;
					vector< vector<Point2f> > tempChessVec2(rows, vector<Point2f>(cols));
					// vector< vector<Point2f> > tempChessVec2(chess_rows, vector<Point2f>(chess_cols));
					makeChessVec(tempChessVec2,corners2);
					invertMultiVec(tempChessVec2);
					vector<Point2f> corners2_new;
					makeSingleVector(tempChessVec2, corners2_new);
					drawChessboardCorners(img_chess_bgr2, boardSize, corners2_new, board_found2);
				}
				else{
					drawChessboardCorners(img_chess_bgr2, boardSize, corners2, board_found2);
				}

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


				

				x = nextPhotoIndex(imgs_directory.c_str());

				char filename1[200], filename2[200];          
				sprintf(filename1, "%s%dl.%s", imgs_directory.c_str(), x, extension.c_str());            
				sprintf(filename2, "%s%dr.%s", imgs_directory.c_str(), x, extension.c_str());

				cout << "Saving img pair " << x << endl;
				// x++;

				
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
