#include "overlay.h"
#include "overlay_api.h"
#include <windows.h>
#include "c_text.h"
#include "c_image.h"

void Overlay::do_overlay(Overlay& overlay) {
    Overlay_validator::validate_overlay_data(overlay);

    std::cout << "Наложение...\n";
    addTextToImage(overlay.local_path_image, overlay.text_pattern, 12, 128);
    ShellExecute(nullptr, "open", "D:\\Proga\\Turovec\\Kursach\\Templates\\output.jpg", nullptr, nullptr, SW_SHOWNORMAL);
}