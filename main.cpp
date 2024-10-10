#include <iostream>
#include <string>
#include "functions.h"
#include "Meme_Gen.h"
using namespace std;


int check_input (int answer)
{
    string number;
    cout << "������� �����: ";
    cin >> number;
    try
    {
        answer = stoi(number);
    }
    catch (const invalid_argument& e)
    {
        cerr << "������: �������� �������� �� �������� ������." << endl;
        return 3;
    }
    catch (const out_of_range& e)
    {
        cerr << "������: �������� ����� ������� �� ������� ����������� ���������." << endl;
        return 3;
    }
    return answer;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "����� ���������� � ��������� �����! ������ ������ �������:\n";

    while(true)
    {
        cout << "1. ����� �������;\n"
                "2. ��������� ���� � ������;\n"
                "0. �����.\n";
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
                cout << "�� ������ ������!\n";
                exit(0);
            default:
                cout << "���������� ��� ���: \n";
                break;
        }
    }
}