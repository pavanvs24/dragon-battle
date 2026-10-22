#include <iostream>
#include "Player.h"
#include <stdexcept>
#include <string>

using namespace std;

Player::Player(const std::string& name)
    : name(name), stable(new Dragon[2]), count(0), capacity(2), stage(1) {}

Player::Player(const Player& other)
    : name(other.name), stable(new Dragon[other.capacity]),
      count(other.count), capacity(other.capacity), stage(other.stage) {
    for (int i = 0; i < count; ++i) stable[i] = other.stable[i];    // deep copy
}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        Dragon* fresh = new Dragon[other.capacity];
        for (int i = 0; i < other.count; ++i) fresh[i] = other.stable[i];
        delete[] stable;
        stable = fresh;
        name = other.name;
        count = other.count;
        capacity = other.capacity;
        stage = other.stage;
    }
    return *this;
}

Player::~Player() {
    delete[] stable;
    stable = nullptr;
}

void Player::grow() {
    if (capacity >= MAX_DRAGONS) return;

    int newCapacity = capacity  + 1;

    Dragon* newStable = new Dragon[newCapacity];
    for (int i = 0; i < count; ++i) {
        newStable[i] = stable[i];
    }
    delete[] stable;
    stable = newStable;
    capacity = newCapacity;
}

bool Player::addDragon(const Dragon& d) {
    if (count == MAX_DRAGONS) return false;
    if (count == capacity) grow();
    stable[count++] = d;
    return true;
}

bool Player::breed(int i, int j) {
    if (count >= MAX_DRAGONS) return false;

    if (i < 0 || i >= count || j < 0 || j >= count || i == j) {
        cout << "Error: Invalid indices for breeding" << endl;
        return false;
    }

    // Rule 1: Child Name (First half of parent 1 + second half of parent 2)
    const Dragon& parent1 = stable[i];
    const Dragon& parent2 = stable[j];
    string name1 = parent1.getName();
    string name2 = parent2.getName();
    string childName = name1.substr(0, name1.length() / 2) + name2.substr(name2.length() / 2);
    
    // Rule 2: Child Element
    string childElement;
    string element1 = parent1.getElement();
    string element2 = parent2.getElement();
    if (element1 == element2) {
        childElement = element1;
    } else {
        childElement = element1 + "/" + element2;
    }

    // Rule 3: Child Stats (Average of parents + 2 boost; HP is average of max HP)
    int childAttack = ((parent1.getAttack() + parent2.getAttack()) / 2) + 2;
    int childDefense = ((parent1.getDefense() + parent2.getDefense()) / 2) + 2;
    int childHP = (parent1.getMaxHp() + parent2.getMaxHp()) / 2;

    Dragon child(childName, childElement, childAttack, childDefense, childHP);

    return addDragon(child);
}

Dragon& Player::getDragon(int index) {
    if (index < 0 || index >= count) {
        cout << "Error: Index out of range" << endl;
        throw std::out_of_range("Index out of range"); // can't return a reference to a non existent dragon, so throw an exception
    }
    return stable[index];
}

const Dragon& Player::getDragon(int index) const {
    if (index < 0 || index >= count) {
        cout << "Error: Index out of range" << endl;
        throw std::out_of_range("Index out of range"); // can't return a reference to a non existent dragon, so throw an exception
    }
    return stable[index];
}

int Player::getCount() const { return count; }

bool Player::hasLivingDragon() const {
    return firstLivingIndex() != -1;
}

int Player::firstLivingIndex() const {
    for (int i = 0; i < count; ++i) {
        if (!stable[i].isFainted()) {
            return i;
        }
    }
    return -1;
}

Player& Player::healAll() {
    for (int i = 0; i < count; ++i) {
        stable[i].heal(stable[i].getMaxHp());
    }
    return *this;
}

const std::string& Player::getName() const { return name; }

int Player::getStage() const { return stage; }

Player& Player::unlockNextStage() {
    if (stage < 3) {
        stage++;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "Player: " << p.name << ", Stage: " << p.stage << ", Stable: (" << p.count << ")" << endl;
    for (int i = 0; i < p.count; ++i) {
        os << "Dragon " << (i + 1) << ": " << p.stable[i].getName() << endl;
    }
    return os ;
}
