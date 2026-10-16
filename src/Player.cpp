// Player.cpp - Owner: Member B
// The constructor, destructor, copy constructor and operator= below are a working reference
// so nobody crashes on a double delete while the rest of the game is built.
// B: read them until you can explain every line in the report, then own them.
#include "Player.h"

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
}

void Player::grow() {
    // TODO(B): new[] a bigger array (cap at MAX_DRAGONS), copy, delete[] the old one
}

bool Player::addDragon(const Dragon& d) {
    // TODO(B): false if count == MAX_DRAGONS; call grow() when count == capacity
    return false;
}

bool Player::breed(int i, int j) {
    // TODO(B): validate i != j and both in range, child = stable[i] + stable[j], addDragon(child)
    return false;
}

Dragon& Player::getDragon(int index) {
    // TODO(B): bounds check
    return stable[index];
}

const Dragon& Player::getDragon(int index) const {
    // TODO(B): bounds check
    return stable[index];
}

int Player::getCount() const { return count; }

bool Player::hasLivingDragon() const {
    // TODO(B)
    return false;
}

int Player::firstLivingIndex() const {
    // TODO(B)
    return -1;
}

Player& Player::healAll() {
    // TODO(B): level-independent full heal of every dragon
    return *this;
}

const std::string& Player::getName() const { return name; }
int Player::getStage() const { return stage; }

Player& Player::unlockNextStage() {
    // TODO(B): stage + 1, capped at 3
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    // TODO(B): name, stage and a numbered list of dragons
    return os << p.name;
}
