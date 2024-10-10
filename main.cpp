#include <iostream>
#include <string>
#include "functions.h"
#include "Meme_Gen.h"
using namespace std;


int check_input (int answer)
{
    string number;
    cout << "Введите число: ";
    cin >> number;
    try
    {
        answer = stoi(number);
    }
    catch (const invalid_argument& e)
    {
        cerr << "Ошибка: введённое значение не является числом." << endl;
        return 3;
    }
    catch (const out_of_range& e)
    {
        cerr << "Ошибка: введённое число выходит за пределы допустимого диапазона." << endl;
        return 3;
    }
    return answer;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Добро пожаловать в генератор мемов! Выбери нужную функцию:\n";

    while(true)
    {
        cout << "1. Выбор шаблона;\n"
                "2. Генерация фото и текста;\n"
                "0. Выйти.\n";
        int choise = 0;

        switch (check_input(choise))
        {
            case 1:
                Generation.setType(choise);
                templates();
                exit(0);
            case 2:
                Generation.setType(choise);
                custom();
                exit(0);
            case 0:
                cout << "До скорых встреч!\n";
                exit(0);
            default:
                cout << "Попробуйте ещё раз: \n";
                break;
        }
    }
}