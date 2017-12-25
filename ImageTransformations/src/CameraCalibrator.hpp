/*
 * CameraCalibrator.hpp
 *
 *  Created on: 2017. 12. 25.
 *      Author: ghbae
 */

#ifndef SRC_CAMERACALIBRATOR_HPP_
#define SRC_CAMERACALIBRATOR_HPP_

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

class CameraCalibrator {
//	std::vector<std::vector<cv::Point3f>> objectPoints;
//	std::vector<std::vector<cv::Point2f>> imagePoints;

	cv::Mat cameraMatrix;
	cv::Mat disCoeffs;

	int flag;

	int addChessboardPoints(const std::vector<std::string>& filelist,
			cv::Size & boardSize);
};



#endif /* SRC_CAMERACALIBRATOR_HPP_ */
