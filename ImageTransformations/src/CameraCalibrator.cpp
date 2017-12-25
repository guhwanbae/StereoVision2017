/*
 * CameraCalibrator.cpp
 *
 *  Created on: 2017. 12. 25.
 *      Author: ghbae
 */

#include "CameraCalibrator.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

int CameraCalibrator::addChessboardPoints(const std::vector<std::string>& filelist,
		cv::Size & boardSize) {
	std::vector<cv::Point2f> imageCorners;
	std::vector<cv::Point3f> objectCorners;

	for(int i=0; i<boardSize.height; i++) {
		for(int j=0; j<boardSize.width; j++) {
			objectCorners.push_back(cv::Point3f(i,j, 0.0f));
		}
	}

	cv::Mat image;
	int successes = 0;

	for(int i=0; i<filelist.size(); i++) {
		//	image = cv::imread(filelist[i], 0);
		bool found = cv::findChessboardCorners(image, boardSize, imageCorners);

		if(found) {
			cv::cornerSubPix(image, imageCorners, cv::Size(5,5), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 30, 0.1));
			if(imageCorners.size() == boardSize.area()) {
				//			addPoints(imageCorners, objectCorners);
				successes++;
			}
		}

		if(imageCorners.size() == boardSize.area()) {
			//		addPoints(imageCorners, objectCorners);
			successes++;
		}
	}

	return successes;
}

