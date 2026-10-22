// Move.cpp - Owner: Member A
#include "Move.h"

Move::Move(const std::string& name, int power, int cooldown)
    : name(name), power(power), cooldown(cooldown), cooldownLeft(0) {}

const std::string& Move::getName() const { return name; }
int  Move::getPower() const { return power; }
bool Move::isReady() const { return cooldownLeft == 0; }

void Move::use() {
    cooldownLeft = cooldown;    
}

void Move::tick() {
    if (cooldownLeft > 0) --cooldownLeft;
}
