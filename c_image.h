#ifndef KURSACH_C_IMAGE_H
#define KURSACH_C_IMAGE_H
#include <string>
#include "custom.h"
#include <iostream>
#include "image_api.h"

using namespace std;

class C_Image : public virtual Custom {
public:

    C_Image() : image_pattern(""), local_path_image("") {};

    C_Image& operator=(const C_Image& other) {
        if (this == &other)
            return *this; // Защита от самоприсваивания

        image_pattern = other.image_pattern;
        local_path_image = other.local_path_image;

        return *this;
    }
    const string &getPattern() const;

    void set_pattern(const string &line);

    string image_pattern;
    string local_path_image;

    string getLocalPath() const { return local_path_image; }
    void setLocalPath(const string& path) { local_path_image = path; }

    ~C_Image() override = default;
};

class I_Settings : public C_Image {
public:
    string image_background;
    string image_color;

    string getImageColor() const;
    void setImageColor(const string& color);


    I_Settings() : image_color(""), image_background("") {}

    I_Settings(const C_Image& base)
            : C_Image(base), // Копируем данные базового класса
              image_background(""), // Устанавливаем значения по умолчанию для новых полей
              image_color("") {}

    // Конструктор копирования (на случай копирования I_Settings)
    I_Settings(const I_Settings& other)
            : C_Image(other),
              image_background(other.image_background),
              image_color(other.image_color) {}

    // Оператор присваивания для полноты
    I_Settings& operator=(const I_Settings& other) {
        if (this == &other)
            return *this;

        C_Image::operator=(other); // Копируем базовый класс
        image_background = other.image_background;
        image_color = other.image_color;

        return *this;
    }

    void apply_settings() override{

    }

    void generate_meme() override {
        std::string fullPrompt = image_pattern +
                                 ", background: " + image_background +
                                 ", main color: " + image_color;

        Image_Api(fullPrompt);
    }

    string getBackgroundColor() const;
    void setBackgroundColor(const string& color);
};

#endif //KURSACH_C_IMAGE_H
