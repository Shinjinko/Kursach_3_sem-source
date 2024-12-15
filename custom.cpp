#include <iostream>
#include "Exp.h"
#include "custom.h"
#include "overlay.h"

Custom::Custom() : meme_type(0) {}

void Custom::setMemeType(int type)
{
    meme_type = type;
}

int Custom::getMemeType() const
{
    return meme_type;
}

void custom() {

    Overlay overlay;
    while (true)
    {
        std::cerr << "Внимание! Все дальнейшие запросы принимаются только на английском языке!\n";
        std::cout << "Выберите тип мема:\n"
                "1. Изображение;\n"
                "2. Текст;\n"
                "3. Наложение;\n"
                "0. Назад.\n";

        switch (Numbers::check_input())
        {
            case 1:
            {
                I_Settings image;
                overlay.local_path_image = image.generate_meme();
                break;
            }
            case 2:
            {
                C_Text text;
                overlay.text_pattern = text.generate_meme();
                break;
            }
            case 3:
                overlay.do_overlay(overlay);
                break;
            case 0:
                return;
            default:
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                break;
        }
    }
}