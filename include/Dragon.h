// Dragon.h - Owner: Member A
#ifndef DRAGON_H
#define DRAGON_H

#include <iostream>
#include <string>
#include "Move.h"

// A battling dragon. Rules (damage, defend, level up, breeding) are in docs/DESIGN.md.
class Dragon {
private:
    std::string name;
    std::string element;
    int  hp, maxHp;
    int  attack, defense;
    int  level;
    bool defending;
    Move moves[2];                  // COMPOSITION: [0] basic attack, [1] special
    static int totalCreated;        // STATIC member

public:
    // Default ctor is for placeholder array slots (e.g. inside Player); it does NOT count.
    Dragon();
    Dragon(const std::string& name, const std::string& element,
           int hp, int attack, int defense);
    Dragon(const Dragon& other);    // copy constructor
    ~Dragon();

    // Getters
    const std::string& getName() const;
    const std::string& getElement() const;
    int  getHp() const;
    int  getMaxHp() const;
    int  getAttack() const;
    int  getDefense() const;
    int  getLevel() const;
    int  getPower() const;          // attack*2 + defense + maxHp/10
    bool isFainted() const;
    bool isDefending() const;
    Move&       getMove(int index); // 0 = basic, 1 = special
    const Move& getMove(int index) const;

    // Actions. They return *this so calls can be chained: d.heal(30).defend();
    Dragon& heal(int amount);
    Dragon& defend();
    Dragon& endTurn();              // ticks move cooldowns, clears defend if needed
    Dragon& levelUp();

    // How much damage this dragon deals to target with a move of the given extra power.
    int damageAgainst(const Dragon& target, int movePower) const;

    // Operator overloading
    Dragon& operator-=(int damage);                 // take damage
    Dragon  operator+(const Dragon& other) const;   // breeding
    bool    operator==(const Dragon& other) const;  // compare by power
    bool    operator<(const Dragon& other) const;
    bool    operator>(const Dragon& other) const;
    Dragon& operator++();                           // prefix: level up
    Dragon  operator++(int);                        // postfix

    // Friends
    friend std::ostream& operator<<(std::ostream& os, const Dragon& d);
    friend std::istream& operator>>(std::istream& is, Dragon& d);
    friend void showStats(const Dragon& d);

    static int getTotalCreated();
};

void showStats(const Dragon& d);    // full stat card

#endif
