
#include "c_image.h"

const std::string &C_Image::getPattern() const
{
    return image_pattern;
}

void C_Image::set_pattern(const std::string &line)
{
    C_Image::image_pattern = line;
}

std::string I_Settings::generate_meme()
{
    GeneratedItem last;
    auto img = last.loadHistory(HISTORY_FILE_TEXTS);

    Social_Media media("");
    std::cout << "Введите запрос для генерации изображения или выберите из ранее сгенерированных: \n"
                 "1. Генерировать;\n"
                 "2. Открыть историю.\n";

    if (Numbers::check_input() == 2)
    {
        return showHistory(img, HISTORY_FILE_TEXTS);
    }
    std::cout << "Введите промт: ";
    getline(std::cin, image_pattern);

    while(true)
    {
        std::cout << "1. Изменить запрос;\n"
                     "0. Далее.\n";

        if(Numbers::check_input())
        {
            getline(std::cin, image_pattern);
        }
        else
            break;
    }

    std::cout << "Желаете открыть расширенные настройки? (1-да/0-нет)\n";

    if (Numbers::check_input())
    {

        std::cout << "Введите промт для фона картинки: ";
        getline(std::cin, image_background);

        std::cout << "Введите промт для основного цвета картинки: ";
        getline(std::cin, image_color);

        std::cout << "Настройки приняты.\n";
    }
    else
    {
        setImageColor("none");
        setBackgroundColor("none");
    }

    std::cout << "Начинается генерация изображения.\n";

    std::string fullPrompt = image_pattern +
                             ", background: " + image_background +
                             ", main color: " + image_color;

    Image_Api(fullPrompt);

    media.local_path = GENERATE_JOKES_PHOTO_OUTPUT;
    ShellExecute(nullptr, "open", GENERATE_JOKES_PHOTO_OUTPUT, nullptr, nullptr, SW_SHOWNORMAL);

    if(media.local_path != "")
    {
        media.distributing(media.local_path);
    }

    last.file_path = GENERATE_JOKES_PHOTO_OUTPUT;
    last.prompt = fullPrompt;

    img.push_back(last);

    saveHistory(img, HISTORY_FILE_TEXTS);
    return GENERATE_JOKES_PHOTO_OUTPUT;
}

std::string I_Settings::getImageColor() const { return image_color; }
void I_Settings::setImageColor(const std::string& color) {}

std::string I_Settings::getBackgroundColor() const { return image_background; }
void I_Settings::setBackgroundColor(const std::string& color) {image_background = color;}
