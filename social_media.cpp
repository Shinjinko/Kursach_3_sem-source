#include "social_media.h"
#include "telegram.h"
#include "vk.h"

void Social_Media::distributing (std::string file_name)
{
    std::cout << "Не желаете распространить мем в социальные сети? (1 - да, 0 - нет)\n";

    if (Numbers::check_input())
    {
        bool exit = false;

        while(!exit)
        {
            std::cout << "1. Телеграмм;\n"
                         "2. Вконтакте;\n"
                         "0. Выйти.\n";
            switch (Numbers::check_input())
            {
                case 1: {
                    Telegram* tg = new Telegram(file_name);
                    tg->distributing(file_name);
                    delete tg;
                    break;
                }
                case 2: {
                    VK* vk = new VK(file_name);
                    vk->distributing(file_name);
                    delete vk;
                    break;
                }
                case 0:
                    exit = true;
                    break;
                default:
                    std::cout << "Неверный набор. Повторите попытку.\n";
                    break;
            }
        }

    }
}