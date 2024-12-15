#ifndef KURSACH_C_IMAGE_H
#define KURSACH_C_IMAGE_H
#include <string>
#include "custom.h"
#include <iostream>
#include "image_api.h"
#include "Exp.h"
#include "last_action.h"
#define GENERATE_JOKES_PHOTO_OUTPUT R"(D:\Proga\Turovec\Kursach\Meme Generator\custom\image.jpg)"

class C_Image : public virtual Custom {
public:
    
    std::string image_pattern;
    mutable std::string local_path_image;

    C_Image() : image_pattern(""), local_path_image("") {};

    C_Image& operator=(const C_Image& other)
            {
        if (this == &other)
            return *this;

        image_pattern = other.image_pattern;
        local_path_image = other.local_path_image;

        return *this;
    }
    const std::string &getPattern() const;

    void set_pattern(const std::string &line);

    std::string getLocalPath() const { return local_path_image; }
    void setLocalPath(const std::string& path) const { local_path_image = path; }

    ~C_Image() override = default;
};

class I_Settings : public C_Image {
public:
    std::string image_background;
    std::string image_color;

    std::string getImageColor() const;
    void setImageColor(const std::string& color);


    I_Settings() : image_background(""), image_color("") {}

    I_Settings(const I_Settings& other)
            : C_Image(other),
              image_background(other.image_background),
              image_color(other.image_color) {}

    I_Settings& operator=(const I_Settings& other) {
        if (this == &other)
            return *this;

        C_Image::operator=(other);
        image_background = other.image_background;
        image_color = other.image_color;

        return *this;
    }

    std::string generate_meme() override;

    std::string getBackgroundColor() const;
    void setBackgroundColor(const std::string& color);

    ~I_Settings() override {}
};

#endif //KURSACH_C_IMAGE_H
