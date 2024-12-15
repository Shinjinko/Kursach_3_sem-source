#include "Exp.h"
#include <iostream>
#include <string>
#include "generate_text.h"
#include "overlay.h"
using namespace std;

jmp_buf Numbers::jumpBuffer;

int Numbers::check_input() {
    string number;
    int answer;

    if (setjmp(jumpBuffer) != 0) {
        cerr << "Попробуйте снова." << endl;
    }

    cout << "\nВведите число: ";
    cin >> number;

    try {
        answer = stoi(number);
    } catch (const invalid_argument& e) {
        cerr << "Ошибка: введённое значение не является числом." << endl;
        longjmp(jumpBuffer, 1);
    } catch (const out_of_range& e) {
        cerr << "Ошибка: введённое число выходит за пределы допустимого диапазона." << endl;
        longjmp(jumpBuffer, 1);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return answer;
}

int Out_of_range::out_of_range(int size)
{
    int index;
    index = Numbers::check_input();
    try
    {
        if (index < 1 || index > size)
            throw string("\nОшибка: введённое число выходит за пределы допустимого диапазона. Ввод округлён до ближайшей границы диапазона.\n");
    }
    catch (string& error_message)
    {
        cout << error_message;
        index = index > size ? size : 1;
    }
    return index;
}

std::string Check_server_answer::validate_and_resend(const std::string& prompt, int max_attempts) {
    std::string response;
    int attempts = 0;

    while (attempts < max_attempts) {
        response = getResponseFromHuggingFace(prompt);

        if (response == "Error: An empty response from the model.") {
            std::cerr << "Error received. Retrying... (" << attempts + 1 << "/" << max_attempts << ")" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            attempts++;
        } else {
            return response;
        }
    }

    std::cerr << "Max attempts reached. Could not get a valid response." << std::endl; // Если не удалось получить корректный ответ
    return "Error: Failed after multiple attempts.";
}

void Overlay_validator::validate_overlay_data(Overlay& overlay)
{
    C_Text text;
    T_Settings text_w_sett;
    I_Settings image;
    bool exit = false;

    if (overlay.getLocalPath() == "") {
        cerr << "Изображение не задано! Запускается генерация.\n";
        overlay.setLocalPath(image.generate_meme());
    }
    if (overlay.getMemeText() == "") {
        cerr << "Текст не задан! Запускается генерация.\n";
        overlay.setMemeText(text.generate_meme());
        text_w_sett.generate_meme();
        overlay.text_color = text_w_sett.text_color;
        overlay.font_size = text_w_sett.font_size;
    }
    if (overlay.font_size == 12)
    {
        text_w_sett.generate_meme();
        overlay.text_color = text_w_sett.text_color;
        overlay.font_size = text_w_sett.font_size;
    }

    while (!exit) {

        cout << "Желаете продолжить наложение?\n"
                "1. Изменить текст;\n"
                "2. Изменить фото;\n"
                "3. Продолжить;\n"
                "0. Выйти.\n";

        switch (Numbers::check_input()) {
            case 1:
                overlay.setLocalPath(text.generate_meme());
                break;
            case 2:
                overlay.setMemeText(image.generate_meme());
                text_w_sett.generate_meme();
                overlay.text_color = text_w_sett.text_color;
                overlay.font_size = text_w_sett.font_size;
                break;
            case 3:
                exit = true;
                break;
            case 0:
                return;
            default:
                cout << "Не верно набран выбор. Попробуйте снова.";
                break;

        }
    }
}

