#include "Utils.h"
#include <iostream>
#include <limits>

namespace Utils {

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int readInt(const std::string& prompt, int low, int high) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (low <= value && value <= high) {
                return value;
            }
            std::cout << "Pick a number between " << low << " and " << high << ".\n";
        }
        else {
            if (std::cin.eof()) {
                return low;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That is not a number. Try again.\n";
        }
    }
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

}