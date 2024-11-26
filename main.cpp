#include <iostream>
#include <string>
#include "functions.h"
#include "Meme_Gen.h"
#include "Exp.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    Meme_Gen Generation;
    cout << "Добро пожаловать в генератор мемов! Выберите нужную функцию:\n";

    while(true)
    {
        cout << "1. Выбор шаблона;\n"
                "2. Генерация фото и текста;\n"
                "0. Выйти.";
        int choise = 0;

        switch (Numbers::check_input())
        {
            case 1:
                Generation.setType(choise);
                templates();
                break;
            case 2:
                Generation.setType(choise);
                custom();
                break;
            case 0:
                cout << "До скорых встреч!\n";
                exit(0);
            default:
                cout << "Попробуйте ещё раз: \n";
                break;
        }
//    TODO:добавить условие на существование текста или изображения    cout << "Отправить творение в социальную сеть Telegram/Vk?";
    }
}