#include "last_action.h"

std::deque<GeneratedItem> GeneratedItem::loadHistory(const std::string& file_history) {
    std::deque<GeneratedItem> history;
    std::ifstream file(file_history);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string prompt, filePath;
        if (std::getline(stream, prompt, '-') && std::getline(stream, filePath)) {
            history.push_back(GeneratedItem(prompt, filePath));
        }
    }

    return history;
}

void saveHistory(const std::deque<GeneratedItem>& history, const std::string& historyFile) {
    std::ofstream file(historyFile, std::ios::trunc);

    for (const auto& item : history) {
        file << item.prompt << "-" << item.file_path << "\n";
    }
}

std::string openFile(const std::deque<GeneratedItem>& history) {
    size_t index;
    std::cout << "Введите номер элемента для открытия: ";
    std::cin >> index;

    if (index > 0 && index <= history.size()) {
        const auto& item = history[index - 1];
        if (std::filesystem::exists(item.file_path)) {
            ShellExecute(NULL, "open", item.file_path.c_str(), NULL, NULL, SW_SHOWNORMAL);
            return item.file_path;
        } else {
            std::cout << "Файл не найден: " << item.file_path << "\n";
        }
    } else {
        std::cout << "Неверный выбор элемента.\n";
    }
    return "";
}

void deleteFile(std::deque<GeneratedItem>& history, const std::string& historyFile) {
    size_t index;
    std::cout << "Введите номер элемента для удаления: ";
    std::cin >> index;

    if (index > 0 && index <= history.size()) {
        auto it = history.begin() + (index - 1);
        if (std::filesystem::exists(it->file_path)) {
            std::filesystem::remove(it->file_path);
        } else {
            std::cout << "Файл не найден: " << it->file_path << "\n";
        }
        history.erase(it);
        saveHistory(history, historyFile);
        std::cout << "Элемент удалён.\n";
    } else {
        std::cout << "Неверный выбор элемента.\n";
    }
}

std::string showHistory(std::deque<GeneratedItem>& history, const std::string& historyFile) {

    if (history.empty()) {
        std::cout << "Нет элементов для отображения.\n";
        return "";
    }

    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << i + 1 << ". " << history[i].prompt << " - " << history[i].file_path << "\n";
    }

    while(true)
    {
        std::cout << "\nМеню:\n"
                     "1. Выбрать элемент для открытия;\n"
                     "2. Удалить элемент;\n"
                     "Ваш выбор: ";

        switch (Numbers::check_input()) {
            case 1:
                return openFile(history);
            case 2:
                deleteFile(history, historyFile);
                break;
            default:
                std::cout << "Неверный выбор.\n";
        }
    }
}