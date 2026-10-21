#include "Game.h"
#include "Battle.h"
#include "Utils.h"
#include <iostream>

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
    // TODO(D): 1 Battle 2 Breed 3 My Stable 4 How to Play 5 Exit
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
    // TODO(D)
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
    std::cout << "Scaffold builds and runs. Nothing is implemented yet.\n";
    // TODO(D): firstRunSetup(); mainMenu();
}
