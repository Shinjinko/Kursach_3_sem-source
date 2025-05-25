#include "overlay.h"
#include "overlay_api.h"

std::string read_file_string(const std::string& filePath) {
    std::ifstream file(filePath); // Открытие файла
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filePath);
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>()); // Чтение
    file.close();
    return content;
}

void Overlay::do_overlay(Overlay& overlay) {
    Overlay_validator::validate_overlay_data(overlay);
    if (overlay.local_path_image == "" || overlay.text_pattern == "")
        return;

    addTextToImage(overlay.local_path_image, read_file_string(overlay.text_pattern), overlay.font_size, overlay.text_color);
    ShellExecute(nullptr, "open", FILENAME_OVERLAY, nullptr, nullptr, SW_SHOWNORMAL);

    Social_Media media(FILENAME_OVERLAY);
    media.distributing(media.local_path);
}