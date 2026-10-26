#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Dragon.h"

class Player {
private:
    std::string name;
    Dragon* stable;     // dynamic array, capacity grows from 2 up to MAX_DRAGONS
    int count;          // dragons currently in the stable
    int capacity;       // allocated slots
    int stage;          // highest unlocked stage, starts at 1

    void grow();        // new[] bigger array, copy, delete[] old

public:
    static const int MAX_DRAGONS = 6;

    Player(const std::string& name = "Trainer");
    Player(const Player& other);                // deep copy
    Player& operator=(const Player& other);     // deep copy, self-assignment safe
    ~Player();                                  // delete[] stable

    // Stable management
    bool addDragon(const Dragon& d);            // false if the stable is full
    bool breed(int i, int j);                   // adds stable[i] + stable[j]; false if invalid or full
    Dragon&       getDragon(int index);         // bounds-checked
    const Dragon& getDragon(int index) const;
    int  getCount() const;
    bool hasLivingDragon() const;
    int  firstLivingIndex() const;              // -1 if all fainted
    Player& healAll();                          // chainable (returns *this)

    // Progress
    const std::string& getName() const;
    int  getStage() const;
    Player& unlockNextStage();                  // chainable

    friend std::ostream& operator<<(std::ostream& os, const Player& p);
};

#endif
