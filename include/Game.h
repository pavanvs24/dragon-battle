#ifndef GAME_H
#define GAME_H

#include "Dragon.h"
#include "Player.h"


class Game {
    private:
        Dragon* catalog;
        int     catalogSize;
        Player* player;

        void buildCatalog();
        void firstRunSetup();
        void mainMenu();
        void startBattle();
        void breedMenu();
        void showStable() const;
        void showCatalog() const;
        void howToPlay() const;
        Player buildSquad(int maxSize, int chosen[]);
        Player buildEnemy(int stage) const;

    public:
        static const int SQUAD_MAX = 3;

        Game();
        ~Game();
        Game(const Game&) = delete;             // owns raw pointers: no copying
        Game& operator=(const Game&) = delete;

        void run();
};

#endif
