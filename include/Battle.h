// Battle.h - Owner: Member C
#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"

// One fight: you versus an enemy trainer. Rules and enemy AI are in docs/DESIGN.md.
class Battle {
private:
    Player& player;         // references: must be set in the constructor's initializer list
    Player& enemy;
    int playerActive;       // index of the dragon currently fighting
    int enemyActive;
    int turn;
    int playerHealsLeft;
    int enemyHealsLeft;

    void showStatus() const;
    bool playerTurn();                  // false if the player forfeits
    void enemyTurn();                   // simple random AI
    void switchIfFainted(Player& who, int& active);

public:
    Battle(Player& player, Player& enemy);
    bool run();                         // true if the player wins
};

#endif
