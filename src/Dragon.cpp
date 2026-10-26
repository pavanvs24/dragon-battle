#include "Dragon.h"
using namespace std;

int Dragon::totalCreated = 0;

Dragon::Dragon()
    : name("Unnamed"), element("Neutral"), hp(100), maxHp(100),
      attack(10), defense(5), level(1), defending(false) {}

Dragon::Dragon(const std::string& name, const std::string& element,
               int hp, int attack, int defense)
    : name(name), element(element), hp(hp), maxHp(hp),
      attack(attack), defense(defense), level(1), defending(false) {
    moves[0] = Move("Bite", 0, 0);
    moves[1] = Move("Special", 15, 3);     
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
    cout << "[Dragon destroyed] " << name << " (" << element << ") removed from memory" << endl;
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
    hp += amount;
    if(hp > maxHp) hp = maxHp;
    return *this;
}

Dragon& Dragon::defend() {
    defending = true;
    return *this;
}

Dragon& Dragon::endTurn() {
    for(int i=0;i<2;i++) {
        moves[i].tick();
    }
    defending = false;
    return *this;
}

Dragon& Dragon::levelUp() {
    level++;maxHp += 10;
    attack += 2;defense += 1;hp = maxHp;
    return *this;
}

int Dragon::damageAgainst(const Dragon& target, int movePower) const {
    int damage = attack + movePower - target.defense;
    if(damage < 1) damage = 1;
    return damage;
}

// ---- Operators ----
Dragon& Dragon::operator-=(int damage) {
    if(defending) {
        damage /= 2;
        if(damage < 1) damage = 1;
        defending = false; 
    }
    hp -= damage;
    if(hp < 0) hp = 0;
    return *this;
}

Dragon Dragon::operator+(const Dragon& other) const {
    int n1 = name.length(), n2 = other.name.length();
    std::string childName = name.substr(0, n1 / 2) + other.name.substr(n2 / 2);

    std::string childElement;
    if (element == other.element) childElement = element;
    else childElement = element + "/" + other.element;

    int childHp      = (maxHp + other.maxHp) / 2;   // average of the two maxHp (no +2)
    int childAttack  = (attack + other.attack) / 2 + 2 ;   // average of the two attacks, then + 2
    int childDefense = (defense + other.defense) / 2 + 2;   // average of the two defenses, then + 2

    Dragon child(childName, childElement, childHp, childAttack, childDefense);
    return child;
}

bool Dragon::operator==(const Dragon& other) const { return getPower() == other.getPower(); }
bool Dragon::operator<(const Dragon& other) const { return getPower() < other.getPower(); }
bool Dragon::operator>(const Dragon& other) const { return getPower() > other.getPower(); }

Dragon& Dragon::operator++() {
    (*this).levelUp();
    return *this;
}

Dragon Dragon::operator++(int) {
    Dragon old(*this);
    (*this).levelUp();
    return old;
}

// ---- Friends ----
std::ostream& operator<<(std::ostream& os, const Dragon& d) {
    return os << d.name << " (" << d.element << ", Lv" << d.level << ") HP " << d.hp << "/" << d.maxHp;
}

std::istream& operator>>(std::istream& is, Dragon& d) {
    is >> d.name >> d.element >> d.hp >> d.attack >> d.defense;
    d.maxHp = d.hp;
    d.defending = false;
    d.moves[0] = Move("Bite", 0, 0);
    d.moves[1] = Move("Special", 15, 3);      
    d.level = 1;
    return is;  
}

void showStats(const Dragon& d) {
    cout << "=== Dragon Stats ===\n";
    cout << "Name: " << d.name << " (" << d.element << ", Lv" << d.level << ") " << endl;
    cout << "HP: " << d.hp << "/" << d.maxHp << endl;
    cout << "Attack: " << d.attack << " Defense: " << d.defense << endl;
    cout << "Power: " << d.getPower() << endl;
    cout << "Status: " << (d.defending ? "Defending" : "Not defending") << endl;    
    cout << "Moves:\n";
    for (int i = 0; i < 2; ++i) {
        cout << "  [" << i << "] " << d.moves[i].getName() << " (Power: " << d.moves[i].getPower()
         << ", " << (d.moves[i].isReady() ? "Ready" : "Cooldown") << ")" << endl;
    }
}

int Dragon::getTotalCreated() { return totalCreated; }
