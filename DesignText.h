#ifndef FILESAPI_DESIGNTEXT_H
#define FILESAPI_DESIGNTEXT_H

#include <iostream>
namespace FilesApi {
    namespace DesignText {
        enum class Color {
            BLACK,
            RED,
            GREEN,
            YELLOW,
            BLUE,
            MAGENTA,
            CYAN,
            WHITE
        };

        std::string make_colored(const std::string &text, Color color, bool bold);
    }
}
#endif //FILESAPI_DESIGNTEXT_H