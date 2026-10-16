// Utils.h - Owner: Member D
#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    // Reads a whole line.
    std::string readLine(const std::string& prompt);

    // Keeps asking until the user enters an integer in [lo, hi].
    int readInt(const std::string& prompt, int lo, int hi);

    // hpBar(70, 100) -> "[#######---]"
    std::string hpBar(int hp, int maxHp, int width = 10);

    void banner(const std::string& title);  // boxed title
    void pause();                           // "Press Enter to continue..."
}

#endif
