#include "Utils.h"
#include <iostream>
#include <limits>
#include <algorithm>

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
    if (hp <= 0 || maxHp <= 0)
        return "[" + std::string(width, '-') + "]";
    
    int fill = hp * width / maxHp;
    fill = std::max(fill, 1);
    fill = std::min(fill, width);

    return "[" + std::string(fill, '#') + std::string(width-fill, '-') + "]";
}

void banner(const std::string& title) {
    int length = title.size();

    std::cout << "+" + std::string(length + 4, '-') + "+\n"
              << "|  " + title + "  |\n"
              << "+" + std::string(length + 4, '-') + "+\n"; 
}

void pause() {
    std::cout << "Press Enter to continue... ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

}