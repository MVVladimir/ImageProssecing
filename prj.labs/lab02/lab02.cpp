#include <opencv2/opencv.hpp>
#include <vector>

void calcHist(std::vector<std::vector<int>>& hist, const cv::Mat& img) {
    for (std::ptrdiff_t i = 0; i < hist.size(); i += 1)
    {
        for (std::ptrdiff_t j = 0; j < hist[i].size(); j += 1)
        {
            hist[i][j] = 0;
        }
    }

    for (std::ptrdiff_t x = 0; x < img.cols; x += 1)
    {
        for (std::ptrdiff_t y = 0; y < img.rows; y += 1)
        {
            hist[0][img.at<cv::Vec3b>(x, y)[0]] += 1;
            hist[1][img.at<cv::Vec3b>(x, y)[1]] += 1;
            hist[2][img.at<cv::Vec3b>(x, y)[2]] += 1;
        }
    }

    for (std::ptrdiff_t i = 0; i < hist.size(); i += 1)
    {
        for (std::ptrdiff_t j = 0; j < hist[i].size(); j += 1)
        {
            std::cout << hist[i][j] << " ";
        }
        std::cout << '\n';
    }
}

int main() {
    std::string filename = "../data/cross_0256x0256.png";
    cv::Mat img_png = cv::imread(filename, cv::IMREAD_COLOR);

    std::vector<int> compression_params;
    compression_params.push_back(75);

    imwrite("./cross_0256x0256_0256.jpg", img_png, compression_params); // Save as jpg with 75 persents loss

    //=============================================================================================

    std::vector<cv::Mat> channels(3);
    cv::split(img_png, channels); // split img to 3 channels - BGR

    cv::Mat zero = cv::Mat::zeros(channels[0].rows, channels[0].cols, channels[0].type());

    std::vector<cv::Mat> red = { zero, zero, channels[2] };
    std::vector<cv::Mat> green = { zero, channels[1], zero };
    std::vector<cv::Mat> blue = { channels[0], zero, zero };

    cv::Mat redChannel, greenChannel, blueChannel;

    cv::merge(red, redChannel);
    cv::merge(green, greenChannel);
    cv::merge(blue, blueChannel);

    std::vector<cv::Mat> upper = { img_png, redChannel };
    std::vector<cv::Mat> bottom = { greenChannel, blueChannel };
    cv::Mat upperPic, bottomPic, img_channels;

    cv::hconcat(upper, upperPic);
    cv::hconcat(bottom, bottomPic);
    cv::vconcat(upperPic, bottomPic, img_channels);
    
    imwrite("./cross_0256x0256_png_channels.png", img_channels);
    imwrite("./cross_0256x0256_jpg_channels.jpg", img_channels, compression_params);

    //=============================================================================================

    std::string filename_jpg = "./cross_0256x0256_0256.jpg";
    cv::Mat img_jpg = cv::imread(filename_jpg, cv::IMREAD_COLOR);

    std::vector<std::vector<int>> hist_jpg(3, std::vector<int>(256));
    std::vector<std::vector<int>> hist_png(3, std::vector<int>(256));

    calcHist(hist_jpg, img_jpg);
    calcHist(hist_png, img_png);
     
}