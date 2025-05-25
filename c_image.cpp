
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
    auto img = last.loadHistory(HISTORY_FILE_IMAGES);
    bool exit = false;

    Social_Media media("");


    while (!exit)
    {
        std::cout << "Введите запрос для генерации изображения или выберите из ранее сгенерированных: \n"
                  "1. Генерировать;\n"
                  "2. Открыть историю;\n"
                  "0. Назад.\n";

        switch (Numbers::check_input()) {
            case 1:
            {
                std::cout << "Введите промт: ";
                getline(std::cin, image_pattern);

                while(!exit)
                {
                    std::cout << "1. Изменить запрос;\n"
                                 "0. Далее.\n";

                    switch (Numbers::check_input()) {
                        case 1:
                            getline(std::cin, image_pattern);
                            break;
                        case 0:
                            exit = true;
                            break;
                        default:
                            std::cout << "Не верный выбор. Попробуйте снова.\n";
                            break;
                    }
                }

                std::cout << "Желаете открыть расширенные настройки? (1 - да/0 - нет)\n";

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

                Image_Api(fullPrompt, img.size());
                std::string local_path_image;
                local_path_image = std::string(GENERATE_JOKES_PHOTO_OUTPUT) + std::to_string(img.size()) + ".jpg";
                media.local_path = local_path_image;
                ShellExecute(nullptr, "open", local_path_image.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

                if(media.local_path != "")
                {
                    media.distributing(media.local_path);
                }

                last.file_path = local_path_image;
                last.prompt = fullPrompt;

                img.push_back(last);

                saveHistory(img, HISTORY_FILE_IMAGES);
                return local_path_image;
            }
            case 2:
            {
                std::string output;
                output = showHistory(img, HISTORY_FILE_IMAGES);
                if (output != "")
                    return output;
                break;
            }
            case 0:
                exit = true;
                break;
            default:
                std::cout << "Не верный выбор. Попробуйте снова.\n";
                break;

        }
    }
    return "";
}

std::string I_Settings::getImageColor() const { return image_color; }
void I_Settings::setImageColor(const std::string& color) {}

std::string I_Settings::getBackgroundColor() const { return image_background; }
void I_Settings::setBackgroundColor(const std::string& color) {image_background = color;}
