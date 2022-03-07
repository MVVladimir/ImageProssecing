## Работа 4. Детектирование границ документов на кадрах видео
автор: Полевой Д.В.
дата: 2022-03-07T11:50:40

### Задание
0. текст, иллюстрации и подписи отчета придумываем самостоятельно
1. самостоятельно снимаем видео смартфоном
- объект съемки - купюры (рубли разного номинала), расправленные и лежащие на поверхности (проективно искаженны прямоугольник)
- количество роликов - от 5 шт.
- длительность - 5-7 сек
- условия съемки разные
2. извлекаем по 3 кадра из каждого ролика (делим кол-во кадров на 5 и берем каждый с индеком 2/5,3/5,4/5)
3. цветоредуцируем изображения
4. бинаризцем изображения
5. морфологически обрабатываем изображения
6. выделяем основную компоненту связности
7. руками изготавливаем маски (идеальная зона купюры)
8. оцениваем качество выделение зоны и анализируем ошибки

### Результаты

### Текст программы

```cpp
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
```
