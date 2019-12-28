#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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
	FileStorage fs("ip.yml", FileStorage::READ);
	string ip;
	fs["ip"] >> ip;
	const string ip_final = ip;
	cout << ip_final << endl;
	return 0;
}