// Utils.cpp - Owner: Member D
#include "Utils.h"
#include <iostream>

namespace Utils {

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int readInt(const std::string& prompt, int lo, int hi) {
    // TODO(D): loop until valid; handle non-numeric input (cin.clear + ignore)
    return lo;
}

std::string hpBar(int hp, int maxHp, int width) {
    // TODO(D): '#' for filled part, '-' for the rest
    return "[" + std::string(width, '-') + "]";
}

void banner(const std::string& title) {
    // TODO(D): nicer box
    std::cout << "=== " << title << " ===\n";
}

void pause() {
    // TODO(D)
}

}   // namespace Utils
