#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    std::string readLine(const std::string& prompt);
    int readInt(const std::string& prompt, int low, int high);
    std::string hpBar(int hp, int maxHp, int width = 10);
    void banner(const std::string& title);
    void pause();
}

#endif
