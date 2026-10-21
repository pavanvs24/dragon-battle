#include "Game.h"
#include "Battle.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

Game::Game() : catalog(nullptr), catalogSize(0), player(nullptr) {
    buildCatalog();
}

Game::~Game() {
    delete[] catalog;
    delete player;
}

void Game::buildCatalog() {
    catalogSize = 8;
    catalog = new Dragon[catalogSize];

    std::string name[] = {"Ember", "Aqua", "Rocky", "Gale", "Frost", "Spark", "Leafy", "Shade"};
    std::string element[] = {"Fire", "Water", "Earth", "Air", "Ice", "Electric", "Nature", "Dark"};
    int attack[] = {26, 20, 18, 24, 22, 28, 19, 25};
    int defence[] = {7, 10, 14, 8, 11, 6, 12, 9};

    for (int i = 0; i < catalogSize; i++) {
        catalog[i] = Dragon(name[i], element[i], 100, attack[i], defence[i]);
    }
}

void Game::firstRunSetup() {
    // TODO(D): ask the name, pick 2 starters (copies of catalog dragons)
}

void Game::mainMenu() {
    int option = 0;
    while (option != 5) {
        std::cout << '\n';
        Utils::banner("MAIN MENU");
        std::cout << "1. Battle (next stage)\n"
             << "2. Breed Dragons\n"
             << "3. My Stable\n"
             << "4. How to Play\n"
             << "5. Exit\n" << std::endl;
        option = Utils::readInt("Pick an option: ", 1, 5);

        switch (option) {
            case 1:
                startBattle();
                Utils::pause();
                break;
            case 2:
                breedMenu();
                Utils::pause();
                break;
            case 3:
                showStable();
                Utils::pause();
                break;
            case 4:
                howToPlay();
                Utils::pause();
                break;
            case 5:
                std::cout << "\nQuitting the Game... See Ya !\n";
                break;
        }
    }
}

void Game::startBattle() {
    // TODO(D): buildEnemy(stage), run a Battle, level-ups / unlockNextStage on win, healAll after
}

void Game::breedMenu() {
    // TODO(D)
}

void Game::showStable() const {
    // TODO(D)
}

void Game::showCatalog() const {
    std::cout << std::left
              << std::setw(4) << "No."
              << std::setw(12) << "Name"
              << std::setw(12) << "Element"
              << std::setw(8) << "HP"
              << std::setw(8) << "ATK"
              << std::setw(8) << "DEF" << '\n';
    
    std::cout << std::string(52, '-') << '\n';

    for (int i = 0; i < catalogSize; i++) {
        std::cout << std::setw(4) << i + 1
                  << std::setw(12) << catalog[i].getName()
                  << std::setw(12) << catalog[i].getElement()
                  << std::setw(8) << catalog[i].getHp()
                  << std::setw(8) << catalog[i].getAttack()
                  << std::setw(8) << catalog[i].getDefense() 
                  << '\n';
    }
}

void Game::howToPlay() const {
    // TODO(D)
}

Player Game::buildEnemy(int stage) const {
    // TODO(D): stages in docs/DESIGN.md
    return Player("Wild Trainer");
}

void Game::run() {
    Utils::banner("DRAGON BATTLE");
    mainMenu();
}
