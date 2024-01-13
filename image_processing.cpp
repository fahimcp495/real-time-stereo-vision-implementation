#include "constants.h"
#include "image_processing.h"

void computeDisparity(image_t *leftImage, image_t *rightImage, image_t *disparityMap) {
    disparityMap->imagesize_x = IMAGE_WIDTH;
    disparityMap->imagesize_y = IMAGE_HEIGHT;

    // Allocate memory for pixel array
    disparityMap->pixel = (int **)malloc(disparityMap->imagesize_x * sizeof(int *));
    for (int i = 0; i < disparityMap->imagesize_x; ++i) {
        disparityMap->pixel[i] = (int *)malloc(disparityMap->imagesize_y * sizeof(int));
    }

    for (int y = 0; y < IMAGE_HEIGHT; ++y) {
        for (int x = 0; x < IMAGE_WIDTH; ++x) {
            int minDifference = 256;  // Initialize with a value higher than possible
            int bestDisparity = 0;

            for (int d = 0; d < MAX_DISPARITY; ++d) {
                int leftPixel = leftImage->pixel[x][y];
                if (x - d < 0)  continue;
                int rightPixel = rightImage->pixel[x - d][y];

                int difference = abs(leftPixel - rightPixel);
                if (difference < minDifference) {
                    minDifference = difference;
                    bestDisparity = d;
                }
            }
            disparityMap->pixel[x][y] = bestDisparity;
        }
    }
}
