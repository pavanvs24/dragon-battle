#include "Game.h"
#include "Battle.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>


Game::Game() : catalog(nullptr), catalogSize(0), player(nullptr) {
    std::cout << "\n[Building Catalog...]\n";
    buildCatalog();
    std::cout << "[Catalog built successfully...]\n\n";
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
    //Trainer Name
    std::string name;
    while (true) {
        name = Utils::readLine("\nEnter your trainer name: ");
        if (name.size() == 0) {
            name = "Trainer";
            std::cout << "\nOK then, We will address you as Trainer :)";
            break;
        }
        else if (name.size() < 3)
            std::cout << "Name should have at least 3 characters.";
        else if (name.size() > 10)
            std::cout << "Name should not have more than 10 characters.";
        else {
            std::cout << "\nWelcome " << name << " !";
            break;
        }
    }
    player = new Player(name);

    //Starter selection
    std::cout << "\nNow, let's get your Starter Dragons set up !\n";
    showCatalog();
    std::cout << '\n';
    int one = Utils::readInt("First Dragon number: ", 1, catalogSize);
    player->addDragon(catalog[one-1]);
    std::cout << " - " << catalog[one-1].getName() << " joined your stable !\n\n";
    int two = Utils::readInt("Second Dragon number: ", 1, catalogSize);
    player->addDragon(catalog[two-1]);
    std::cout << " - " << catalog[two-1].getName() << " joined your stable !\n\n";

    std::cout << "Nice... You are all Set to Go !";
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
    Utils::banner("BATTLE");
    int stage = player->getStage();

    int chosen[SQUAD_MAX];
    Player squad = buildSquad(SQUAD_MAX, chosen);
    Player enemy = buildEnemy(stage);

    Battle b(squad, enemy);
    bool won = b.run();

    if (won) {
        //Level up
        for (int i = 0; i < squad.getCount(); i++)
            ++player->getDragon(chosen[i]);
        
        player->unlockNextStage();
        std::cout << "\n - Stage " << stage << " Cleared !";
        std::cout << "\n - Your Dragons grew stronger !\n";
    }
    else
        std::cout << "\n - DEFEAT...\n";
}

void Game::breedMenu() {
    if (player == nullptr)
        return;
    
    int n = player->getCount();
    showStable();
    if (n < 2) {
        std::cout << "\n - You need at least 2 dragons to breed\n";
        return;
    }
    if (player->getCount() >= player->MAX_DRAGONS) {
        std::cout << "\n - Your stable is full\n";
        return;
    }

    std::cout << '\n';
    int first = Utils::readInt("Select first parent: ", 1, n);
    int second = Utils:: readInt("Select second parent: ", 1, n);
    
    if (first == second) {
        std::cout << "\n - Same dragons cannot be bred\n";
        return;
    }
    bool bred = player->breed(first-1, second-1);
    if (!bred) {
        std::cout << "\n - Oops, The breeding failed...\n";
        return;
    }
    std::cout << "\n - A new dragon was born !\n\n";
    showStats(player->getDragon(n));
}

void Game::showStable() const {
    Utils::banner("STABLE");
    std::cout << *player;
}

void Game::showCatalog() const {
    std::cout << '\n';
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
    Utils::banner("HOW TO PLAY");
    std::cout << "- Goal: beat all 3 stages by knocking out every enemy dragon\n"
              << "- Moves: Attack, Special (3-turn cooldown), Defend (halves the next hit), Heal (+30 HP, 3 uses per battle), Switch (costs your turn)\n"
              << "- Damage: your attack plus the move's power, minus the target's defense, with a minimum of 1\n"
              << "- Winning a stage: your dragons level up, and the next stage unlocks\n"
              << "- Breeding: two different dragons in your stable make a new one (max 6 dragons)\n\n";
}

Player Game::buildSquad(int maxSize, int chosen[]) {
    Player squad("squad");
    int size = (player->getCount() > maxSize) ? maxSize : player->getCount();
    
    showStable();
    std::cout << '\n';
    for (int i = 0; i < size; i++) {
        int choice = Utils::readInt("Pick Dragon " + std::to_string(i+1) + ": ", 1, player->getCount());
        bool duplicate = false;
        for (int  k = 0; k < i; k++) {
            if (chosen[k] + 1 == choice) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            std::cout << "That dragon is already selected.\n";
            i--;
            continue;
        }
        chosen[i] = choice - 1;
        squad.addDragon(player->getDragon(choice - 1));
    }
    return squad;
}

Player Game::buildEnemy(int stage) const {
    Player enemy("Wild Trainer");
    int teamSize = (stage == 1) ? 2 : 3;

    for (int i = 0; i < teamSize; i++) {
        int selector = rand() % catalogSize;
        enemy.addDragon(catalog[selector]);

        for (int k = 0; k < stage - 1; k++)
            ++enemy.getDragon(i);
    }
    return enemy;
}

void Game::run() {
    srand(static_cast<unsigned>(time(0)));
    Utils::banner("DRAGON BATTLE");
    firstRunSetup();
    mainMenu();
}
