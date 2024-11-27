#include "overlay.h"
#include "overlay_api.h"
//#include <windows.h>

void Overlay::do_overlay(const Overlay& overlay) {
    Overlay_validator::validate_overlay_data(overlay);

    cout << "Наложение...\n";
    addTextToImage(overlay.local_path_image, overlay.text_pattern, overlay.font_size, 128);
//    ShellExecute(nullptr, "open", "D:\\Proga\\Turovec\\Kursach\\Templates\\output.jpg", nullptr, nullptr, SW_SHOWNORMAL);
}