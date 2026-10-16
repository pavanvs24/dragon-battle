// Dragon.cpp - Owner: Member A
// Stubs: getters and constructors work; everything marked TODO(A) still needs real logic.
#include "Dragon.h"

int Dragon::totalCreated = 0;

Dragon::Dragon()
    : name("Unnamed"), element("Neutral"), hp(100), maxHp(100),
      attack(10), defense(5), level(1), defending(false) {}

Dragon::Dragon(const std::string& name, const std::string& element,
               int hp, int attack, int defense)
    : name(name), element(element), hp(hp), maxHp(hp),
      attack(attack), defense(defense), level(1), defending(false) {
    moves[0] = Move("Bite", 0, 0);
    moves[1] = Move("Special", 15, 3);      // TODO(A): per-element special names
    ++totalCreated;
}

Dragon::Dragon(const Dragon& other)
    : name(other.name), element(other.element), hp(other.hp), maxHp(other.maxHp),
      attack(other.attack), defense(other.defense), level(other.level),
      defending(other.defending) {
    moves[0] = other.moves[0];
    moves[1] = other.moves[1];
    ++totalCreated;
}

Dragon::~Dragon() {
    // TODO(A): decide on a destructor message for the report screenshot
}

// ---- Getters ----
const std::string& Dragon::getName() const { return name; }
const std::string& Dragon::getElement() const { return element; }
int  Dragon::getHp() const { return hp; }
int  Dragon::getMaxHp() const { return maxHp; }
int  Dragon::getAttack() const { return attack; }
int  Dragon::getDefense() const { return defense; }
int  Dragon::getLevel() const { return level; }
int  Dragon::getPower() const { return attack * 2 + defense + maxHp / 10; }
bool Dragon::isFainted() const { return hp <= 0; }
bool Dragon::isDefending() const { return defending; }
Move&       Dragon::getMove(int index) { return moves[index]; }
const Move& Dragon::getMove(int index) const { return moves[index]; }

// ---- Actions (chainable) ----
Dragon& Dragon::heal(int amount) {
    // TODO(A): add amount, never above maxHp
    return *this;
}

Dragon& Dragon::defend() {
    // TODO(A): set defending
    return *this;
}

Dragon& Dragon::endTurn() {
    // TODO(A): tick both moves, clear defending when the rule says so
    return *this;
}

Dragon& Dragon::levelUp() {
    // TODO(A): level +1, maxHp +10, attack +2, defense +1, hp = maxHp
    return *this;
}

int Dragon::damageAgainst(const Dragon& target, int movePower) const {
    // TODO(A): max(1, attack + movePower - target.defense)
    return 1;
}

// ---- Operators ----
Dragon& Dragon::operator-=(int damage) {
    // TODO(A): halve if defending (min 1), clamp hp at 0
    return *this;
}

Dragon Dragon::operator+(const Dragon& other) const {
    // TODO(A): breeding rules in docs/DESIGN.md
    return Dragon();
}

bool Dragon::operator==(const Dragon& other) const { return getPower() == other.getPower(); }
bool Dragon::operator<(const Dragon& other) const { return getPower() < other.getPower(); }
bool Dragon::operator>(const Dragon& other) const { return getPower() > other.getPower(); }

Dragon& Dragon::operator++() {
    // TODO(A): call levelUp()
    return *this;
}

Dragon Dragon::operator++(int) {
    // TODO(A): return the old value, then level up
    return *this;
}

// ---- Friends ----
std::ostream& operator<<(std::ostream& os, const Dragon& d) {
    // TODO(A): one-line summary, e.g. Ember (Fire, Lv2) HP 70/100
    return os << d.name;
}

std::istream& operator>>(std::istream& is, Dragon& d) {
    // TODO(A): read name, element, hp, attack, defense
    return is;
}

void showStats(const Dragon& d) {
    // TODO(A): full stat card using private members
    std::cout << d << "\n";
}

int Dragon::getTotalCreated() { return totalCreated; }
