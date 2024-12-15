#include "color_map.h"

ColorMap::ColorMap() {
    color_map = {
            {"red", cv::Scalar(0, 0, 255)},
            {"green", cv::Scalar(0, 255, 0)},
            {"blue", cv::Scalar(255, 0, 0)},
            {"yellow", cv::Scalar(0, 255, 255)},
            {"cyan", cv::Scalar(255, 255, 0)},
            {"magenta", cv::Scalar(255, 0, 255)},
            {"black", cv::Scalar(0, 0, 0)},
            {"white", cv::Scalar(255, 255, 255)}
    };
}

void ColorMap::addColor(const std::string& name, const cv::Scalar& value) {
    std::string lower_name = toLowerCase(name);
    color_map[lower_name] = value;
}

void ColorMap::removeColor(const std::string& name) {
    std::string lower_name = toLowerCase(name);
    if (color_map.erase(lower_name) == 0) {
        throw std::invalid_argument("Цвет не найден: " + name);
    }
}

cv::Scalar ColorMap::getColor(const std::string& name) const {
    std::string lower_name = toLowerCase(name);
    auto it = color_map.find(lower_name);
    if (it != color_map.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Цвет не найден: " + name);
    }
}

bool ColorMap::hasColor(const std::string& name) const {
    return color_map.find(toLowerCase(name)) != color_map.end();
}

auto ColorMap::begin() const { return color_map.begin(); }
auto ColorMap::end() const { return color_map.end(); }

std::string ColorMap::toLowerCase(const std::string& str) const {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return lower_str;
}