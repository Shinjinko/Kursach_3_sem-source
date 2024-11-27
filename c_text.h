#ifndef KURSACH_C_TEXT_H
#define KURSACH_C_TEXT_H
#include <iostream>
#include <string>
#include <opencv2/core/types.hpp>
#include "custom.h"

using namespace std;

class C_Text : public virtual Custom {
public:
    string getMemeText() const;
    void setMemeText(const string& text) const;

    void apply_settings() override {
        cout << "Применение настроек для изображения." << endl;
    }
    void generate_meme() override {
        std::string prompt = "Helen";
//TODO: нормально вызвать функцию генерации текста
        string response;
        cin >> response;

        std::cout << "Final Answer: " << response << std::endl;
    }

    mutable string text_pattern;
};

class T_Settings : public C_Text {
private:
    string text_background;
    string text_font;
public:
    string text_color;
    int font_size;

    const string getTextColor() const ;
    void setTextColor(string color);

    const string &getTextFont() const;
    void setTextFont(const string& font);

    int getFontSize() const;
    void setFontSize(int size);

    const string &getTextBackground() const;
    void setTextBackground(const string &textBackground);

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
