#include <string>
#include <fstream>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\stitching\stitcher.hpp>

#pragma comment(lib, "opencv_core2411d.lib")
#pragma comment(lib, "opencv_imgproc2411d.lib")
#pragma comment(lib, "opencv_highgui2411d.lib")
#pragma comment(lib, "opencv_stitching2411d.lib");
using namespace cv;
using namespace std;

bool fexists(const string&);

String panName = "pantest3";

/*
This algorithm constructs a panorama out of a series of images.
The images should be in C:/panorama/<panName>/ where <panName> is the above variable.
The images should be named pan0.jpg, pan1.jpg, ..., panN.jpg where N is the Nth image.
The result will be saved as C:/panorama/<panName>.jpg
*/

void main()
{
	vector<Mat> imageList;
	Mat panorama;

	String nextImageFileName;
	nextImageFileName = "C:/panorama/" + panName + "/pan0.jpg";
	for(int i = 1; fexists(nextImageFileName); i++) {
		imageList.push_back(imread(nextImageFileName.c_str()));
		nextImageFileName = "C:/panorama/" + panName + "/pan"+to_string(i)+".jpg";
	}

	Stitcher stitcher = Stitcher::createDefault();

	stitcher.stitch(imageList, panorama);

	imshow("Stitching Result", panorama);
	imwrite("C:/panorama/"+panName+".jpg", panorama);

	waitKey(0);
}

bool fexists(const string& filename) {
	ifstream ifile(filename.c_str());
	return ifile;
}