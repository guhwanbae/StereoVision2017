/*
 * main.cpp
 *
 *  Created on: 2017. 12. 4.
 *      Author: ghbae
 */

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	string imgLeftPath, imgRightPath;
	cout << "Type Left image path : ";
	getline(cin, imgLeftPath);
	cout << "Type Left Right path : ";
	getline(cin, imgRightPath);

	Mat left, right;
	left = imread(imgLeftPath);
	right = imread(imgRightPath);

	Mat rectifiedLeft, rectifiedRight;
	//rectifiedLeft = imread("left.png", IMREAD_GRAYSCALE);
	//rectifiedRight = imread("right.png", IMREAD_GRAYSCALE);
	cvtColor(left, rectifiedLeft, CV_RGB2GRAY);
	cvtColor(right, rectifiedRight, CV_RGB2GRAY);
	Mat disparity16S = Mat( rectifiedLeft.rows, rectifiedLeft.cols, CV_16S );
	Mat disparity8U = Mat( rectifiedLeft.rows, rectifiedLeft.cols, CV_8UC1 );

	namedWindow("RECTIFIED_LEFT_SAMPLE");
	imshow("RECTIFIED_LEFT_SAMPLE", left);
	namedWindow("RECTIFIED_RIGHT_SAMPLE");
	imshow("RECTIFIED_RIGHT_SAMPLE", right);

	int ndisparities = 16*5; // Range of disparity.
	int SADWindowSize = 21; // Size of block window.

	Ptr<StereoBM> sbm = StereoBM::create(ndisparities, SADWindowSize);
	sbm->compute(rectifiedLeft, rectifiedRight, disparity16S);

	double minVal; double maxVal; // Check its extreme values
	minMaxLoc(disparity16S, &minVal, &maxVal);

	disparity16S.convertTo( disparity8U, CV_8UC1, 255/(maxVal - minVal)); // Display it as a CV_8UC1 image

	namedWindow("DISPARITY_WINDOW");
	imshow("DISPARITY_WINDOW", disparity8U );
	imwrite("disparity_map.jpg", disparity8U);

	double min, max;
	minMaxIdx(disparity8U, &min, &max);
	Mat adjustDisparity;
	disparity8U.convertTo(adjustDisparity, CV_8UC1, 255/max);
	Mat tonedMap;
	applyColorMap(adjustDisparity, tonedMap, COLORMAP_AUTUMN);
	namedWindow("TONED_DISPARITY_WINDOW");
	imshow("TONED_DISPARITY_WINDOW", tonedMap);
	imwrite("toned_disparity_map.jpg", tonedMap);

	waitKey(0);
	return 0;
}
