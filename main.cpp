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
    cout << "����� ���������� � ��������� �����! �������� ������ �������:\n";

    while(true)
    {
        cout << "1. ����� �������;\n"
                "2. ��������� ���� � ������;\n"
                "0. �����.";
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
                cout << "�� ������ ������!\n";
                exit(0);
            default:
                cout << "���������� ��� ���: \n";
                break;
        }
//    TODO:�������� ������� �� ������������� ������ ��� �����������    cout << "��������� �������� � ���������� ���� Telegram/Vk?";
    }
}