#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "opencv2/opencv.hpp"

#include <string>
#include "image_struct.h"

void savePGM(const std::string& filename, const cv::Mat& image);
void readPGMP2(image_t *image, const char *filename);
void writePGMP2(const char *filename, const image_t *image);

#endif // FILE_OPERATIONS_H
