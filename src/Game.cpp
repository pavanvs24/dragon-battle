// Game.cpp - Owner: Member D
#include "Game.h"
#include "Battle.h"
#include "Utils.h"
#include <iostream>

Game::Game() : catalog(nullptr), catalogSize(0), player(nullptr) {
    // TODO(D): buildCatalog()
}

Game::~Game() {
    delete[] catalog;
    delete player;
}

void Game::buildCatalog() {
    // TODO(D): new Dragon[8] filled from the table in docs/DESIGN.md
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
    Utils::banner("ELEMENTAL DRAKES");
    std::cout << "Scaffold builds and runs. Nothing is implemented yet.\n";
    // TODO(D): firstRunSetup(); mainMenu();
}
