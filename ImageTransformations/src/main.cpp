/*
 * main.cpp
 *
 *  Created on: 2017. 12. 11.
 *      Author: guhwan.bae
 */

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "Constant.hpp"

using namespace cv;
using namespace std;

vector<Point2f> ptsSrc;
vector<Point2f> ptsDst;

int numSrcCorners = 0;
int numDstCorners = 0;

void CallBackFuncSrc(int event, int x, int y, int flags, void* userdata)
{
	if  ( event == EVENT_LBUTTONDOWN && numSrcCorners < 4 )
	{
		numSrcCorners++;
		// Four corners of the book in source image.
		ptsSrc.push_back(Point2f(x, y));
		cout << "Sample Source Corners(" << numSrcCorners << ") : (" << x << ", " << y << ")" << endl;
	}
}

void CallBackFuncDst(int event, int x, int y, int flags, void* userdata)
{
	if  ( event == EVENT_LBUTTONDOWN && numDstCorners < 4 )
	{
		numDstCorners++;
		// Four corners of the book in destination image.
		ptsDst.push_back(Point2f(x, y));
		cout << "Sample Destination Corners(" << numDstCorners << ") : (" << x << ", " << y << ")" << endl;
	}
}

int main( int argc, char** argv)
{
	string imgSrcPath, imgDstPath;
	cout << "Type Source image path : ";
	getline(cin, imgSrcPath);

	cout << "Click 4 points above source image." << endl;
    // Read source image.
    Mat imgSrc = imread(imgSrcPath);
    resize(imgSrc, imgSrc, Size(RESIZED_WIDTH, RESIZED_HEIGHT));

	//if fail to read the image
	if ( imgSrc.empty() )
	{
		cout << "Fail to read the image." << endl;
		return -1;
	}

	//Create a window
	namedWindow(SRC_WINDOW, CV_WINDOW_AUTOSIZE);
	//set the callback function for any mouse event
	setMouseCallback(SRC_WINDOW, CallBackFuncSrc, NULL);
	//Show source sample
	imshow(SRC_WINDOW, imgSrc);
	// Wait for selecting corners.
	waitKey(0);

	cout << "Type Destination image path : ";
	getline(cin, imgDstPath);

    // Read destination image.
    Mat imgDst = imread(imgDstPath);
    resize(imgDst, imgDst, Size(RESIZED_WIDTH, RESIZED_HEIGHT));
	//Create a window
	namedWindow(DST_WINDOW, CV_WINDOW_AUTOSIZE);
	//set the callback function for any mouse event
	setMouseCallback(DST_WINDOW, CallBackFuncDst, NULL);
	//Show destination sample
	imshow(DST_WINDOW, imgDst);

	// Wait for selecting corners.
	waitKey(0);

    // Calculate Homography
    Mat h = findHomography(ptsSrc, ptsDst);

    // Output image
    Mat imgOut;
    // Warp source image to destination based on homography
    warpPerspective(imgSrc, imgOut, h, imgDst.size());

    // Display images
    namedWindow("OutputImage", CV_WINDOW_AUTOSIZE);
    imshow("OutputImage", imgOut);
    imwrite("sample_output.jpg", imgOut);

    waitKey(0);
}


