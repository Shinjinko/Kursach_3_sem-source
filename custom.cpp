#include <iostream>
#include <string>
#include <windows.h>
#include "Exp.h"
#include "custom.h"
#include "overlay.h"
#include "generate_text.h"
//#include "overlay_api.h"
//#include <C:\Users\HONOR\.vcpkg-clion\installed\x64-mingw-dynamic\include\opencv3\opencv2\opencv.hpp>

using namespace std;

Custom::Custom() : meme_type(0) {}

void Custom::setMemeType(int type)
{
    meme_type = type;
}

int Custom::getMemeType() const
{
    return meme_type;
}

string c_image ()
{
    I_Settings *image = new I_Settings;
    cout << "������� ������ ��� ��������� �����������: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, image->image_pattern);

    while(true)
    {
        cout << "1. �������� ������;\n"
                "0. �����.\n";

            if(Numbers::check_input())
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, image->image_pattern);
            }
            else
                break;
    }

    cout << "������� ������� ����������� ���������? (1-��/0-���)\n";

    if (Numbers::check_input())
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        C_Image* oldImage = image;
        image = new I_Settings(*oldImage);
        delete oldImage;

        cout << "������� ����� ��� ���� ��������: ";
        getline(cin, image->image_background);

        cout << "������� ����� ��� ��������� ����� ��������: ";
        getline(cin, image->image_color);

        cout << "��������� �������.\n";
    }
    else
    {
        image->setImageColor("none");
        image->setBackgroundColor("none");
    }

    image->generate_meme();
    ShellExecute(nullptr, "open", "output.jpg", nullptr, nullptr, SW_SHOWNORMAL);
    delete image;
    return "output.jpg";
}

string c_text() {
    T_Settings* textSettings = new T_Settings;

    std::cout << "������� ����� ��� ���������: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, textSettings->text_pattern);

    while (true) {
        std::cout << "1. �������� �����;\n"
                  << "0. �����.\n";

        int choice;
        if (Numbers::check_input()) {
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������
        } else {
            break;
        }

        if (choice == 1) {
            std::cout << "������� ����� �����: ";
            std::getline(std::cin, textSettings->text_pattern);
        } else {
            break;
        }
    }

    std::cout << "������� ��������� ��������� ������? (1-��/0-���): ";
    int settingsChoice;
    if (Numbers::check_input()) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������
        std::cin >> settingsChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������

        if (settingsChoice == 1) {
            std::cout << "������� ���� ������: ";
            string color;
            cin >> color;
            textSettings->setTextColor(color);

            std::cout << "������� ����� ������: ";
            std::string font;
            std::getline(std::cin, font);
            textSettings->setTextFont(font);

            std::cout << "������� ��� ������: ";
            std::string background;
            std::getline(std::cin, background);
            textSettings->setTextBackground(background);

            std::cout << "������� ������ ������: ";
            int fontSize;
            std::cin >> fontSize;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������
            textSettings->setFontSize(fontSize);
        }
    } else {
        textSettings->setTextColor("default");
        textSettings->setTextFont("default");
        textSettings->setTextBackground("default");
        textSettings->setFontSize(12);
    }

    std::string prompt = textSettings->text_pattern +
                         ", color: " + "12" +
                         ", font: " + textSettings->getTextFont() +
                         ", background: " + textSettings->getTextBackground() +
                         ", font size: " + std::to_string(textSettings->getFontSize());

    std::cout << "�������� ������� � �������:\n" << prompt << std::endl;

    std::string generatedText = getResponseFromHuggingFace(prompt);

    if (!generatedText.empty()) {
        std::cout << "��������������� �����:\n" << generatedText << std::endl;
    } else {
        std::cout << "������ ��� ��������� ������." << std::endl;
    }

    delete textSettings;
    return generatedText;
}

void custom() {

//TODO: ��������� ���� ����������

    Overlay overlay;
    while (true)
    {
        cerr << "��������! ��� ���������� ������� ����������� ������ �� ���������� �����!\n";
        cout << "�������� ��� ����:\n"
                "1. �����������;\n"
                "2. �����;\n"
                "3. ���������;\n"
                "0. �����.\n";

        switch (Numbers::check_input())
        {
            case 1:
                c_image();
                break;
            case 2:
                c_text();
                break;
            case 3:
                overlay.do_overlay(overlay);
                break;
            case 0:
                return;
            default:
                cout << "�������� �����. ���������� �����." << endl;
                break;
        }
    }
}