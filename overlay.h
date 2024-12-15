#ifndef KURSACH_OVERLAY_H
#define KURSACH_OVERLAY_H
#include "c_text.h"
#include "c_image.h"
#include <windows.h>
#include <unordered_map>

class Overlay : public I_Settings, public T_Settings
{
public:
    Overlay()
    {
        local_path_image = "";
        text_pattern = "";
    }

    std::string generate_meme() override
    { return "";}

    void do_overlay (Overlay& overlay);

    ~Overlay() override = default;
};

std::string read_file_string(const std::string& filePath);
#endif //KURSACH_OVERLAY_H