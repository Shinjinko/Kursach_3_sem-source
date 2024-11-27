#ifndef KURSACH_C_TEXT_H
#define KURSACH_C_TEXT_H
#include <iostream>
#include <string>
#include <opencv2/core/types.hpp>
#include "custom.h"


class C_Text : public virtual Custom {
public:
    std::string getMemeText() const;
    void setMemeText(const std::string& text) const;

    void apply_settings() override {
        std::cout << "Применение настроек для изображения." << std::endl;
    }
    void generate_meme() override {
        std::string prompt = "Helen";
//TODO: нормально вызвать функцию генерации текста
        std::string response;
        std::cin >> response;

        std::cout << "Final Answer: " << response << std::endl;
    }

    mutable std::string text_pattern;
};

class T_Settings : public C_Text {
private:
    std::string text_background;
    std::string text_font;
public:
    std::string text_color;
    int font_size;

    const std::string getTextColor() const ;
    void setTextColor(std::string color);

    const std::string &getTextFont() const;
    void setTextFont(const std::string& font);

    int getFontSize() const;
    void setFontSize(int size);

    const std::string &getTextBackground() const;
    void setTextBackground(const std::string &textBackground);

    T_Settings() : text_color(""), text_font(""), text_background(""), font_size(12) {}

    void apply_settings() override{
        //Добавить возможность возврата
    }

    void generate_meme() override {
        apply_settings();
        C_Text::generate_meme();
        //привязать
    }
};
#endif //KURSACH_C_TEXT_H
