#ifndef KURSACH_COLOR_MAP_H
#define KURSACH_COLOR_MAP_H

#include <string>
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <cctype>
#include <stdexcept>

class ColorMap {
private:
    std::unordered_map<std::string, cv::Scalar> color_map;

public:
    ColorMap(); // Конструктор по умолчанию

    void addColor(const std::string& name, const cv::Scalar& value);
    void removeColor(const std::string& name);
    cv::Scalar getColor(const std::string& name) const;
    bool hasColor(const std::string& name) const;

    auto begin() const;
    auto end() const;

private:
    std::string toLowerCase(const std::string& str) const;
};

#endif //KURSACH_COLOR_MAP_H
