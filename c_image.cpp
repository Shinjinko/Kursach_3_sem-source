#include "c_image.h"

const string &C_Image::getPattern() const
{
    return image_pattern;
}

void C_Image::set_pattern(const string &line)
{
    C_Image::image_pattern = line;
}

string I_Settings::getImageColor() const { return image_color; }
void I_Settings::setImageColor(const string& color) {}

string I_Settings::getBackgroundColor() const { return image_background; }
void I_Settings::setBackgroundColor(const string& color) {image_background = color;}