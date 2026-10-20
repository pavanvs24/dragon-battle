// Battle.cpp - Owner: Member C
#include <cstdlib>
#include "Battle.h"
#include "Utils.h"

Battle::Battle(Player& player, Player& enemy)
    : player(player), enemy(enemy), playerActive(0), enemyActive(0),
      turn(1), playerHealsLeft(3), enemyHealsLeft(3) {}

void Battle::showStatus() const {
    // TODO(C): header line + both active dragons with Utils::hpBar
    const Dragon& mine = player.getDragon(playerActive);
    const Dragon& foe = player.getDragon(enemyActive);
    std::cout << "--- Stage " << player.getStage() << " | Turn " << turn << " ---\n";
    std::cout << "You:   " << mine.getName() << " "
              << Utils::hpBar(mine.getHp(),mine.getMaxHp()) << " " 
              << mine.getHp() << "/" << mine.getMaxHp() << " " 
              << "(" << mine.getElement() << ", Lv" <<mine.getLevel() <<")\n";
    std::cout << "Enemy: " << foe.getName() << " "
              << Utils::hpBar(foe.getHp(),foe.getMaxHp()) << " " 
              << foe.getHp() << "/" << foe.getMaxHp() << " " 
              << "(" << foe.getElement() << ", Lv" <<foe.getLevel() <<")\n";
}
/*--- Stage 1 | Turn 3 ---
You:   Ember [#######---] 70/100 (Fire, Lv2)
Enemy: Rocky [####------] 40/100 (Earth, Lv1)
*/

bool Battle::playerTurn() {
    // TODO(C): menu 1 Attack 2 Special 3 Defend 4 Heal 5 Switch 6 Stats 7 Forfeit
    Dragon& mine = player.getDragon(playerActive);
    Dragon& foe  = enemy.getDragon(enemyActive);
    
    bool acted = false; 
    while(!acted){
        std::cout << "1. Attack  2. Special  3. Defend  4. Heal (" << playerHealsLeft <<" left)  5. Switch  6. Stats  7. Forfeit\n";
        int choice = Utils::readInt("Choose: ",1,7);
        if (choice == 1) {
            // 1. get the move's power
            int power = mine.getMove(0).getPower();
            // 2. work out the damage
            int damage = mine.damageAgainst(foe,power);
            // 3. remember the enemy's HP before the hit
            int before = foe.getHp();
            // 4. apply the damage
            foe-= damage;
            // 5. print what happened
            std::cout << mine.getName() << " uses " << mine.getMove(0).getName() << " on " << foe.getName() << " for " << before - foe.getHp() << " damage!\n";
            acted = true;
        }
        if (choice == 2){
            if(mine.getMove(1).isReady()){
                int power = mine.getMove(1).getPower();
                int damage = mine.damageAgainst(foe,power);
                int before = foe.getHp();
                foe -= damage;
                mine.getMove(1).use();
                std::cout << mine.getName() << " uses " << mine.getMove(1).getName() << " on " << foe.getName() << " for " << before - foe.getHp() << " damage!\n";
                acted = true;
            }
            else{
                std::cout << "Special is still under cooldown!\n";
            }

        }
        if (choice == 3){
            mine.defend();
            std::cout <<  mine.getName() << " braces for the next hit!\n";
            acted = true;
        }
        if (choice == 4) {
            if (playerHealsLeft > 0) {
                // 1. remember HP before
                int before = mine.getHp();
                // 2. heal 30
                mine.heal(30);

                // 3. use up one heal
                playerHealsLeft--;
                // 4. print how much HP was gained
                std::cout << mine.getName() << " heals with " << mine.getHp()-before <<" HP \n"; 
                // 5. acted = true;
                acted = true;
            } else {
                std::cout <<"No heals left!\n";
                // print "No heals left!"
            }
        
        }
        if (choice == 5) {
            // piece 1: show the stable
            for (int i = 0; i < player.getCount(); i++){
                const Dragon& d = player.getDragon(i);
                std::cout << i + 1 << ". " << d.getName() << " " << d.getHp() << "/" << d.getMaxHp();
                if (d.isFainted()) {
                    std::cout << " (fainted)";
                }
                std::cout << "\n";
            }
            // piece 2: read which dragon to switch to
            int pick = Utils::readInt("Switch to: ", 1, player.getCount()) - 1;
            // piece 3: check the pick, then switch
            if (pick == playerActive){
                std::cout << "Already Fighting!\n";
            }
            else if (player.getDragon(pick).isFainted()){
                std::cout << "The Dragon has fainted!\n";
            }
            else{
                playerActive = pick;
                std::cout << "The player has picked " << player.getDragon(pick).getName() <<'\n';
                acted = true;
            }
        }
        if (choice == 6){
            std::cout << "\n--- Your dragon ---\n";
            showStats(mine);
            std::cout << "\n--- Enemy dragon ---\n";
            showStats(foe);
            std::cout << "\n";
        }
        if (choice == 7){
            std::cout << player.getName() << " forfeits the battle!\n";
            return false;
        }
    }
    return true;
}    
    

void Battle::enemyTurn() {
    // TODO(C): roll 1-100, rules in docs/DESIGN.md
    std::cout << "Enemy's Turn\n";
    Dragon& mine = enemy.getDragon(enemyActive);
    Dragon& foe  = player.getDragon(playerActive);
    int roll = rand() % 100 + 1;
    bool attacking = false;

    if (roll <= 70) {
        attacking = true;
    } else if (roll <= 90) {
        mine.defend();
        std::cout <<  mine.getName() << " braces for the next hit!\n";
    } else {
        if (enemyHealsLeft>0 && mine.getHp() < mine.getMaxHp()/2){
            int before = mine.getHp();
            mine.heal(30);
            enemyHealsLeft--;
            std::cout << mine.getName() << " heals with " << mine.getHp()-before <<" HP \n"; 
        }
        else {
            attacking = true;
        }
    }

    if (attacking) {
            int power = mine.getMove(0).getPower();
            int damage = mine.damageAgainst(foe,power);
            int before = foe.getHp();
            foe-= damage;
            std::cout << mine.getName() << " uses " << mine.getMove(0).getName() << " on " << foe.getName() << " for " << before - foe.getHp() << " damage!\n";
    }
}

void Battle::switchIfFainted(Player& who, int& active) {
    // TODO(C): move to the next living dragon (free switch)
    // 1. if the active dragon has NOT fainted, return right away
    if (!who.getDragon(active).isFainted()){
        return;
    }    
    // 2. find the next living dragon with who.firstLivingIndex()
    int next = who.firstLivingIndex();

    // 3. if the result is not -1:
        if (next!=-1){
          active = next;
          std::cout << who.getDragon(next).getName() <<" enters the battle arena!\n";  
        }
}

bool Battle::run() {
    // TODO(C): loop until one side has no living dragon; return true if the player won
    std::cout << "[Battle not implemented yet]\n";
    return false;
}
