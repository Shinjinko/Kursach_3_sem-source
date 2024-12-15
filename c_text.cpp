#include "c_text.h"
#include "last_action.h"
#include "color_map.h"

std::string C_Text::getMemeText() const { return text_pattern; }
void C_Text::setMemeText(const std::string& text) const { text_pattern = text; }

cv::Scalar T_Settings::getTextColor() const { return text_color;}

void T_Settings::setTextColor(std::string color_name)
{
    static ColorMap colorMap;

    while (true) {
        try {
            text_color = colorMap.getColor(color_name); // Получение цвета из контейнера
            return;
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << " Попробуйте снова: \n";

            std::cout << "Введите цвет (на английском): ";
            std::string new_color;
            std::cin >> new_color;
            color_name = new_color; // Переопределяем имя цвета
        }
    }
}

int T_Settings::getFontSize() const { return font_size; }
void T_Settings::setFontSize(int size) { font_size = size; }

std::string T_Settings::generate_meme()
{
    std::cout << "Желаете настроить параметры текста? (1 - да / 0 - нет): ";
    if (Numbers::check_input())
    {
            std::cout << "Введите цвет (на английском): ";
            std::string color;
            std::cin >> color;
            setTextColor(color);

            std::cout << "Введите размер шрифта: ";
            int fontSize;
            std::cin >> fontSize;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            setFontSize(fontSize);

    } else {
        setTextColor("black");
        setFontSize(10);
    }
    return "";
}

std::string C_Text::generate_meme()
{
    GeneratedItem last;
    auto img = last.loadHistory(HISTORY_FILE_TEXTS);

    Social_Media media("");

    std::cout << "Введите текст для генерации или используйте ранее сгенерированные: \n"
                "1. Генерировать;\n"
                "2. Открыть историю.\n";
    if (Numbers::check_input() == 2)
    {
        return showHistory(img, HISTORY_FILE_TEXTS);
    }
    std::cout << "Введите промт: ";
    std::getline(std::cin, text_pattern);

    while (true) {
        std::cout << "1. Изменить текст;\n"
                  << "0. Далее.\n";

        if (Numbers::check_input()) {
            std::cout << "Введите новый текст: ";
            std::getline(std::cin, text_pattern);
        } else {
            break;
        }
    }

    std::cout << "Отправка запроса с данными:\n" << text_pattern << std::endl;

    std::string generatedText = Check_server_answer::validate_and_resend(text_pattern);

    if (!generatedText.empty()) {
        std::cout << "Сгенерированный текст:\n" << generatedText << std::endl;
    } else {
        std::cout << "Ошибка при генерации текста." << std::endl;
    }

    std::string tempFilePath = GENERATE_JOKES_TEXT_OUTPUT;
    std::ofstream tempFile(tempFilePath);

    tempFile << generatedText;
    media.local_path = generatedText;
    tempFile.close();
    ShellExecute(nullptr, "open", tempFilePath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

    if(media.local_path != "")
    {
        media.distributing(media.local_path);
    }

    last.file_path = GENERATE_JOKES_TEXT_OUTPUT;
    last.prompt = text_pattern;

    img.push_back(last);

    saveHistory(img, HISTORY_FILE_IMAGES);

    return GENERATE_JOKES_TEXT_OUTPUT;
}