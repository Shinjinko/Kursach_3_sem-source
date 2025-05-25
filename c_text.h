#ifndef KURSACH_C_TEXT_H
#define KURSACH_C_TEXT_H
#include <iostream>
#include <string>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core.hpp>
#include "custom.h"
#include <fstream>
#include <unordered_map>
#include "Exp.h"
#define GENERATE_JOKES_TEXT_OUTPUT R"(D:\Proga\Turovec\Kursach\Meme Generator\custom\jokes_output)"

class C_Text : public virtual Custom {
public:
    std::string getMemeText() const;
    void setMemeText(const std::string& text) const;

    std::string generate_meme() override;

    mutable std::string text_pattern;
};

class T_Settings : public C_Text {
public:
    cv::Scalar text_color;
    int font_size;
    bool change;

    cv::Scalar getTextColor() const;
    void setTextColor(std::string color_name);

    int getFontSize() const;
    void setFontSize(int size);

    T_Settings() : text_color(0, 0, 0), font_size(12), change(false) {}

    std::string generate_meme() override;
};
#endif //KURSACH_C_TEXT_H
