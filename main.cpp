#include <iostream>
#include "functions.h"
#include "Meme_Gen.h"
#include "Exp.h"

int main() {
    system("chcp 65001");

    Meme_Gen Generation;

    std::cout << "Добро пожаловать в генератор мемов! Выберите нужную функцию:\n";

    while (true) {
        std::cout << "1. Выбор шаблона;\n"
                     "2. Генерация фото и текста;\n"
                     "0. Выйти.";
        int choise = 0;

        switch (Numbers::check_input()) {
            case 1:
                Generation.setType(choise);
                templates();
                break;
            case 2:
                Generation.setType(choise);
                custom();
                break;
            case 0:
                std::cout << "До скорых встреч!\n";
                exit(0);
            default:
                std::cout << "Попробуйте ещё раз: \n";
                break;
        }
    }
}