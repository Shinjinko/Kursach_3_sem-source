#include "c_text.h"

std::string C_Text::getMemeText() const { return text_pattern; }
void C_Text::setMemeText(const std::string& text) const { text_pattern = text; }

const std::string T_Settings::getTextColor() const { return text_color; }
void T_Settings::setTextColor(std::string color) { text_color = color; }

const std::string &T_Settings::getTextFont() const { return text_font; }
void T_Settings::setTextFont(const std::string& font) { text_font = font; }

int T_Settings::getFontSize() const { return font_size; }
void T_Settings::setFontSize(int size) { font_size = size; }

const std::string &T_Settings::getTextBackground() const { return text_background; }
void T_Settings::setTextBackground(const std::string &textBackground) { text_background = textBackground; }