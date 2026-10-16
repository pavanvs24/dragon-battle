// Move.h - Owner: Member A
#ifndef MOVE_H
#define MOVE_H

#include <string>

// One attack a dragon can perform.
// Dragon uses it through COMPOSITION (a Dragon "has" Moves).
class Move {
private:
    std::string name;
    int power;          // added on top of the dragon's attack stat
    int cooldown;       // turns the move is unusable after being used
    int cooldownLeft;

public:
    Move(const std::string& name = "Tackle", int power = 0, int cooldown = 0);

    const std::string& getName() const;
    int  getPower() const;
    bool isReady() const;
    void use();         // starts the cooldown
    void tick();        // call once per turn: reduces cooldownLeft
};

#endif
