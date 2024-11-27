#include "Exp.h"
#include <iostream>
#include <string>
#include "generate_text.h"
#include "custom.h"
#include "overlay.h"
using namespace std;

jmp_buf Numbers::jumpBuffer;

int Numbers::check_input() {
    string number;
    int answer;

    if (setjmp(jumpBuffer) != 0) {
        cerr << "���������� �����." << endl;
    }

    cout << "\n������� �����: ";
    cin >> number;

    try {
        answer = stoi(number);
    } catch (const invalid_argument& e) {
        cerr << "������: �������� �������� �� �������� ������." << endl;
        longjmp(jumpBuffer, 1);
    } catch (const out_of_range& e) {
        cerr << "������: �������� ����� ������� �� ������� ����������� ���������." << endl;
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
            throw string("\n������: �������� ����� ������� �� ������� ����������� ���������. ���� ������� �� ��������� ������� ���������.\n");
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

    std::cerr << "Max attempts reached. Could not get a valid response." << std::endl; // ���� �� ������� �������� ���������� �����
    return "Error: Failed after multiple attempts.";
}

void Overlay_validator::validate_overlay_data(Overlay& overlay)
{
    if (overlay.getLocalPath() == "") {
        cerr << "����������� �� ������! ����������� ���������.\n";
        overlay.setLocalPath(c_image());
    }
    if (overlay.getMemeText() == "") {
        cerr << "����� �� �����! ����������� ���������.\n";
        overlay.setMemeText(c_text());
    }
}