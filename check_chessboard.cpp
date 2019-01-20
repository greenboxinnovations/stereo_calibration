#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace cv;
using namespace std;

static bool readStringList( const string& filename, vector<string>& l )
{
    l.resize(0);
    FileStorage fs(filename, FileStorage::READ);
    if( !fs.isOpened() )
        return false;
    FileNode n = fs.getFirstTopLevelNode();
    if( n.type() != FileNode::SEQ )
        return false;
    FileNodeIterator it = n.begin(), it_end = n.end();
    for( ; it != it_end; ++it )
        l.push_back((string)*it);
    return true;
}




void chessboardShow(const vector<string>& imagelist, Size boardSize){

	int i, k, nimages = (int)imagelist.size()/2;
	cout << nimages << " pairs found." << endl;

	const string winname1 = "first";
	const string winname2 = "second";

	namedWindow(winname1, 0 );
	namedWindow(winname2, 0 );

	resizeWindow(winname1, 1280, 960);
	resizeWindow(winname2, 1280, 960);

	vector<Point2f> corners1;
	vector<Point2f> corners2;

	if( imagelist.size() % 2 != 0 )
    {
        cout << "Error: the image list contains odd (non-even) number of elements\n";
        return;
    }



    for( i = 0; i < nimages; i++ )
    {
    	const string& filename1 = imagelist[i*2+0];
    	const string& filename2 = imagelist[i*2+1];
        Mat img1 = imread(filename1, 0);
        Mat img2 = imread(filename2, 0);

        bool found1 = false;
        bool found2 = false;
        found1 = findChessboardCorners(img1, boardSize, corners1,
                    CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

        found2 = findChessboardCorners(img2, boardSize, corners2,
                    CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

        cout << filename1 << " - " << filename2 << endl;
        Mat cimg1, cimg2;
        cvtColor(img1, cimg1, COLOR_GRAY2BGR);
        cvtColor(img2, cimg2, COLOR_GRAY2BGR);
        drawChessboardCorners(cimg1, boardSize, corners1, found1);
        drawChessboardCorners(cimg2, boardSize, corners2, found2);        
        // resize(cimg, cimg1, Size(), sf, sf, INTER_LINEAR_EXACT);
        // imshow("corners", cimg1);
        imshow(winname1, cimg1);
        imshow(winname2, cimg2);
        char c = (char)waitKey(5000);
        if( c == 27 || c == 'q' || c == 'Q' ) //Allow ESC to quit
            exit(-1);
    }

}



int main(int argc, char** argv)
{
	string imagelistfn;

    if(argc < 2){
        cout << "usage:\n./check_chessboard <img_list.yml>" << endl;
        return 0;
    }

	imagelistfn = argv[1];

	vector<string> imagelist;
    bool ok = readStringList(imagelistfn, imagelist);
    if(!ok || imagelist.empty())
    {
        cout << "can not open " << imagelistfn << " or the string list is empty" << endl;
        return 1;
    }


    chessboardShow(imagelist, Size(13,9));

    return 0;
}