#ifndef KURSACH_LAST_ACTION_H
#define KURSACH_LAST_ACTION_H

#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <sstream>
#include <filesystem>
#include <cstdlib>
#include <windows.h>
#include "Exp.h"

#define HISTORY_FILE_TEXTS R"(D:\Proga\Turovec\Kursach\Meme Generator\history\generated_texts_history.txt)"
#define HISTORY_FILE_IMAGES R"(D:\Proga\Turovec\Kursach\Meme Generator\history\generated_images_history.txt)"


class GeneratedItem {
public:
    std::string prompt;
    std::string file_path;

    static std::deque<GeneratedItem> loadHistory(const std::string& historyFile);

    GeneratedItem() = default;
    GeneratedItem(const std::string& prompt, const std::string& filePath)
            : prompt(prompt), file_path(filePath) {}
};


void saveHistory(const std::deque<GeneratedItem>& history, const std::string& historyFile);

std::string openFile(const std::deque<GeneratedItem>& history);

void deleteFile(std::deque<GeneratedItem>& history, const std::string& historyFile);

std::string showHistory(std::deque<GeneratedItem>& history, const std::string& historyFile);

#endif //KURSACH_LAST_ACTION_H
