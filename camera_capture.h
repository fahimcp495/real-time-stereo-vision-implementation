#ifndef CAMERA_CAPTURE_H
#define CAMERA_CAPTURE_H

#include "opencv2/opencv.hpp"
#include <thread>


int capture();
int processImages(cv::Mat leftImage, cv::Mat rightImage);
int displayImages(std::string leftImagePath, std::string disparityImagePath, std::string rightImagePath);

#endif // CAMERA_CAPTURE_H
