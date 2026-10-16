// Game.h - Owner: Member D
#ifndef GAME_H
#define GAME_H

#include "Dragon.h"
#include "Player.h"

// Top level: owns the catalog and your profile, runs the menus.
class Game {
private:
    Dragon* catalog;        // read-only starter dragons (dynamic array)
    int     catalogSize;
    Player* player;         // the one profile on this device; null until first-run setup

    void buildCatalog();
    void firstRunSetup();
    void mainMenu();
    void startBattle();
    void breedMenu();
    void showStable() const;
    void showCatalog() const;
    void howToPlay() const;
    Player buildEnemy(int stage) const;     // hard-coded enemy teams for stages 1 to 3

public:
    Game();
    ~Game();
    Game(const Game&) = delete;             // owns raw pointers: no copying
    Game& operator=(const Game&) = delete;

    void run();
};

#endif
