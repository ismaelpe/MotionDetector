#include <stdio.h>
#include <format>
#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
    float threshold = 0.09;
    cv::VideoCapture cap = cv::VideoCapture(0);
    cv::Mat image, read_image, read_image_gray, read_image_gray_old, substract, out_image;

    for (;;) {
        if (cap.read(image)) { 
            float x_mid = image.cols / 2.0;
            float y_mid = image.rows / 2.0;

            //cv::GaussianBlur(image, read_image, cv::Size(5, 5), 1.5);    
            cv::cvtColor(image, read_image_gray, cv::COLOR_BGR2GRAY); 

            if (!read_image_gray_old.empty()) {
                cv::absdiff(read_image_gray, read_image_gray_old, substract);
                cv::threshold(substract, out_image, 50, 125, cv::THRESH_BINARY);

                // Resize original Image
                cv::Mat originalImageResized;
                cv::resize(image, originalImageResized, cv::Size(x_mid, y_mid));

                // Resize transformed Image
                cv::Mat transformImageResized;
                cv::resize(out_image, transformImageResized, cv::Size(x_mid, y_mid));
                // Now we need transform output image (gray) to color image to paste in same mat.
                cv::Mat transformImageResizedColor;
                cv::cvtColor(transformImageResized, transformImageResizedColor, cv::COLOR_GRAY2BGR); 
                
                
                // Prepare visualization
                cv::Mat fullOutput;
                
                // Set banner Top
                cv::Mat imageBannerTop;
                cv::hconcat(originalImageResized, transformImageResizedColor, imageBannerTop);
                
                // Set banner Bottom
                cv::Mat imageBannerBottom;
                cv::Mat imageBannerLeftBottom = cv::Mat::zeros(y_mid, x_mid, imageBannerTop.type());
                cv::Mat imageBannerRightBottom = cv::Mat::zeros(y_mid, x_mid, imageBannerTop.type());

                // Calcuate movement in binary image
                cv::Scalar tempVal = cv::mean( out_image );
                float myMAtMean = tempVal.val[0];
                
                putText(imageBannerLeftBottom, cv::format("AVG: %f - threshold: %f - Size: %dx%d ", myMAtMean, threshold, image.cols, image.rows), cv::Point(0, 12), cv::FONT_HERSHEY_DUPLEX, 0.5, CV_RGB(255, 255, 255), 1);
                
                cv::hconcat(imageBannerLeftBottom, imageBannerRightBottom, imageBannerBottom);

                if (tempVal.val[0] > threshold) {
                    putText(imageBannerBottom, "Move detect!!", cv::Point(x_mid - 120.0, y_mid / 2.0), cv::FONT_HERSHEY_DUPLEX, 1.5, CV_RGB(255, 255, 255), 1);
                }

                // Add banners to fullOutput
                cv::vconcat(imageBannerTop, imageBannerBottom, fullOutput);

                cv::imshow("Viewer", fullOutput);

                if (cv::waitKey(1) >= 0) {
                    break;
                }
            } 

            read_image_gray_old = read_image_gray.clone();
        }
    } 
    return 0;
}
