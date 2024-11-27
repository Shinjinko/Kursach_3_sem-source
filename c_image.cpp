#include "c_image.h"

const std::string &C_Image::getPattern() const
{
    return image_pattern;
}

void C_Image::set_pattern(const std::string &line)
{
    C_Image::image_pattern = line;
}

std::string I_Settings::getImageColor() const { return image_color; }
void I_Settings::setImageColor(const std::string& color) {}

std::string I_Settings::getBackgroundColor() const { return image_background; }
void I_Settings::setBackgroundColor(const std::string& color) {image_background = color;}
