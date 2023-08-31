#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>

char map_value(int x , int x_min, int x_max, int y_min, int y_max);
void print_vec(std::vector<char> ascii_chars, int width, int height);
int camera_to_ascii(int width, int height);

int main() {
    int width;
    int height;
    std::cout << "Set width:" << std::endl;
    std::cin >> width;
    std::cout << "Set height:" << std::endl;
    std::cin >> height;
    

    camera_to_ascii(width, height);
}


char map_value(int x , int x_min, int x_max, int y_min, int y_max){
    // Ensure that x is within the source range
    if (x > x_max || x < x_min) std::cout << "Error: x value is not in the range";

    // Perform the linear interpolation
    int y = (x - x_min) * (y_max - y_min) / (x_max - x_min) + y_min;

    return y;
}

int camera_to_ascii(int width, int height){
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    int desired_width = width; //320
    int desired_height = height;

    std::string ascii_chars = "                                        .'`^,:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Error: Captured empty frame." << std::endl;
            break;
        }

        cv::resize(frame, frame, cv::Size(desired_width, desired_height));


        std::vector<char> ascii_vec;
        for (int y = 0; y < desired_height; y++){
            for (int x = 0; x < desired_width; x++){
                cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);

                // BGR
                int brightness = pixel[0] * 0.0722 + pixel[1] * 0.7152 + pixel[2] * 0.2126;

                ascii_vec.push_back(ascii_chars[map_value(brightness, 0, 255, 0, ascii_chars.length() - 1)]);
            }
        }

        print_vec(ascii_vec, desired_width, desired_height);
        sleep(0.033);

        if (cv::waitKey(1) == 27)
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}

void print_vec(std::vector<char> ascii_chars, int width, int height){
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            std::cout << ascii_chars[x + width * y];
        }
        std::cout << std::endl;
    }
}