#ifndef TESTAPIOVERLAY_OVERLAY_H
#define TESTAPIOVERLAY_OVERLAY_H
#include <iostream>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define FILENAME_OVERLAY R"(D:\Proga\Turovec\Kursach\Meme Generator\custom\overlay.jpg)"

void addTextToImage(const std::string& imagePath, const std::string& text, int fontSize, const cv::Scalar& color) {

    cv::Mat image = cv::imread(imagePath);

    if (image.empty()) {
        std::cerr << "Ошибка: не удалось загрузить изображение!" << std::endl;
        return;
    }

    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = fontSize / 10.0;
    int thickness = 2;
    int baseline = 0;

    cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);
    cv::Point textOrg((image.cols - textSize.width) / 2, (image.rows + textSize.height) / 2);

    cv::putText(image, text, textOrg, fontFace, fontScale, color, thickness);

    cv::imwrite(FILENAME_OVERLAY, image);
}
#endif //TESTAPIOVERLAY_OVERLAY_H