#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

double f(const double  x) {
    return 45.95 * std::log(x + 1.);
}  

int main() {
    std::string filename = "../data/cross_0256x0256.png";
    cv::Mat img_png = cv::imread(filename, cv::IMREAD_COLOR);

    imwrite("lab03_rgb.png", img_png);

    //========================VISUALIZING=THE=FUNCTION========================

    cv::Mat viz_func(512, 512, CV_8UC1);
    viz_func = 255;

    std::vector<uint8_t> lut256(256);

    for (size_t i = 0; i < lut256.size(); i += 1)
    {
        lut256[i] = std::ceil(f(i));
    }

    for (std::ptrdiff_t i = 0; i < viz_func.cols; i += 1)
    {
        std::cout << viz_func.rows - f(i) << '\n';
        viz_func.at<uint8_t>(viz_func.rows - 1 - f(i) * 1.783, i) = 0;
    }

    imwrite("lab03_viz_func.png", viz_func);

    //========================CONVERTING=TO=GRAYSCALE=AND=SCALING=======================

    cv::Mat img_grey, img_gre_res;

    cv::cvtColor(img_png, img_grey, cv::COLOR_BGR2GRAY);

    cv::LUT(img_grey, lut256, img_gre_res);

    imwrite("lab03_gre_res.png", img_gre_res);
    imwrite("lab03_gre.png", img_grey);

    //=========================SCALING=BGR======================

    cv::Mat rgb_res;

    std::vector<cv::Mat> channels(3);
    cv::split(img_png, channels); // split img to 3 channels - BGR

    cv::LUT(channels[0], lut256, channels[0]);
    cv::LUT(channels[1], lut256, channels[1]);
    cv::LUT(channels[2], lut256, channels[2]);

    cv::merge(channels, rgb_res);

    imwrite("lab03_rgb_res.png", rgb_res);
}