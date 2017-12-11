/*
 * main.cpp
 *
 *  Created on: 2017. 12. 11.
 *      Author: guhwan.bae
 */

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Constant.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if  ( event == EVENT_LBUTTONDOWN )
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
}

int main(int argc, char** argv)
{
	cout << "This program outputs the pixel coordinate when you click the image on the window." << endl;

	// Read image from file
	Mat img = imread(SAMPLE_PATH);

	//if fail to read the image
	if ( img.empty() )
	{
		cout << "Fail to read the image." << endl;
		return -1;
	}

	// Resize source image
	Mat resized;
	resize(img, resized, Size(RESIZED_WIDTH, RESIZED_HEIGHT));

	//Create a window
	namedWindow(NAMED_WINDOW, CV_WINDOW_AUTOSIZE);

	//set the callback function for any mouse event
	setMouseCallback(NAMED_WINDOW, CallBackFunc, NULL);

	//show the image
	imshow(NAMED_WINDOW, resized);

	// Wait until user press some key
	waitKey(0);

	//write and save the resized image
	imwrite(RESIZED_PATH, resized);

	return 0;

}


