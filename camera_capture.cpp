#include "constants.h"
#include "camera_capture.h"
#include "file_operations.h"
#include "image_processing.h"
#include "image_struct.h"
#include <iostream>
#include <string>



// Implementation of the capture function
int capture() {
    // Open the first camera
    cv::VideoCapture cap1(2, cv::CAP_V4L2);

    if (!cap1.isOpened()) {
        std::cerr << "Error opening camera 1." << std::endl;

        return -1;
    }

    // Open the second camera
    cv::VideoCapture cap2(4, cv::CAP_V4L2);
    if (!cap2.isOpened()) {
        std::cerr << "Error opening camera 2." << std::endl;
        return -1;
    }

    // int frameWidth = 450;
    // int frameHeight = 375;
    cap1.set(cv::CAP_PROP_FRAME_WIDTH, IMAGE_WIDTH);
    cap1.set(cv::CAP_PROP_FRAME_HEIGHT, IMAGE_HEIGHT);
    cap2.set(cv::CAP_PROP_FRAME_WIDTH, IMAGE_WIDTH);
    cap2.set(cv::CAP_PROP_FRAME_HEIGHT, IMAGE_HEIGHT);

    while (true) {
        cv::Mat frame1, frame2;

        // Capture frame from camera 1
        cap1 >> frame1;
        if (frame1.empty()) {
            std::cerr << "Error capturing frame from camera 1." << std::endl;
            return -1;
        }

        // Capture frame from camera 2
        cap2 >> frame2;
        if (frame2.empty()) {
            std::cerr << "Error capturing frame from camera 2." << std::endl;
            return -1;
        }

        processImages(frame1, frame2);

    }
    return 0;
}

// Implementation of the processImages function
int processImages(cv::Mat leftImage, cv::Mat rightImage) {
    // // Save in .png format
    imwrite("leftImage.png", leftImage);
    imwrite("rightImage.png", rightImage);

    // // Save in .pgm format
    savePGM("leftImage.pgm", leftImage);
    savePGM("rightImage.pgm", rightImage);

    // Save in image struct
    image_t   image_left, image_right, image_disp;
    readPGMP2(&image_left, std::string("leftImage.pgm").c_str());
    readPGMP2(&image_right, std::string("rightImage.pgm").c_str());

    computeDisparity(&image_left, &image_right, &image_disp);

    writePGMP2(std::string("dispImage.pgm").c_str(), &image_disp);
    // writePGMP2(rightImage.c_str(), image_right);


    displayImages("leftImage.png", "dispImage.pgm", "rightImage.png");
    return 0;
}

// Implementation of the displayImages function
int displayImages(std::string leftImagePath, std::string disparityImagePath, std::string rightImagePath) {
    // Load images with desired color treatments
    cv::Mat image1 = cv::imread(leftImagePath, cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread(disparityImagePath, cv::IMREAD_GRAYSCALE);
    cv::Mat image3 = cv::imread(rightImagePath, cv::IMREAD_COLOR);

    // Check if images are loaded successfully
    if (image1.empty() || image2.empty() || image3.empty()) {
        std::cerr << "Failed to load one or more images." << std::endl;
        return -1;
    }

    // Ensure all images have the same number of rows (height)
    int maxRows = std::max({image1.rows, image2.rows, image3.rows});
    int maxCols = image1.cols + image2.cols + image3.cols;

    // Resize images to match the maximum height
    cv::resize(image1, image1, cv::Size(maxCols / 3, maxRows));
    cv::resize(image2, image2, cv::Size(maxCols / 3, maxRows));
    cv::resize(image3, image3, cv::Size(maxCols / 3, maxRows));

    // Convert grayscale image to three channels
    cv::Mat image2Color;
    cv::cvtColor(image2, image2Color, cv::COLOR_GRAY2BGR);

    // Concatenate the images horizontally
    cv::Mat result;
    cv::hconcat(image1, image2Color, result);
    cv::hconcat(result, image3, result);

    // Display the concatenated image
    cv::imshow("Images", result);

    // Wait for a short duration to allow the window to update
    cv::waitKey(1);

    // Wait for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}
