#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "opencv2/opencv.hpp"
#include "image_struct.h"

void computeDisparity(image_t *leftImage, image_t *rightImage, image_t *disparityMap);

#endif // IMAGE_PROCESSING_H
