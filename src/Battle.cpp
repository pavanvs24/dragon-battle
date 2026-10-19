// Battle.cpp - Owner: Member C
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
    return true;
}

void Battle::enemyTurn() {
    // TODO(C): roll 1-100, rules in docs/DESIGN.md
}

void Battle::switchIfFainted(Player& who, int& active) {
    // TODO(C): move to the next living dragon (free switch)
}

bool Battle::run() {
    // TODO(C): loop until one side has no living dragon; return true if the player won
    std::cout << "[Battle not implemented yet]\n";
    return false;
}
