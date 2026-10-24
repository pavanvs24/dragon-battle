// Battle.cpp - Owner: Member C
#include <cstdlib>
#include "Battle.h"
#include "Utils.h"

Battle::Battle(Player &player, Player &enemy)
    : player(player), enemy(enemy), playerActive(0), enemyActive(0),
      turn(1), playerHealsLeft(3), enemyHealsLeft(3) {}

void Battle::showStatus() const
{
    const Dragon &mine = player.getDragon(playerActive);
    const Dragon &foe = enemy.getDragon(enemyActive);
    std::cout << "\n--- Stage " << player.getStage() << " | Turn " << turn << " ---\n";
    std::cout << "You:   " << mine.getName() << " "
              << Utils::hpBar(mine.getHp(), mine.getMaxHp()) << " "
              << mine.getHp() << "/" << mine.getMaxHp() << " "
              << "(" << mine.getElement() << ", Lv" << mine.getLevel() << ")\n";
    std::cout << "Enemy: " << foe.getName() << " "
              << Utils::hpBar(foe.getHp(), foe.getMaxHp()) << " "
              << foe.getHp() << "/" << foe.getMaxHp() << " "
              << "(" << foe.getElement() << ", Lv" << foe.getLevel() << ")\n";
}

bool Battle::playerTurn()
{
    Dragon &mine = player.getDragon(playerActive);
    Dragon &foe = enemy.getDragon(enemyActive);

    bool acted = false;
    while (!acted)
    {
        std::cout << "1. Attack  2. Special  3. Defend  4. Heal (" << playerHealsLeft << " left)  5. Switch  6. Stats  7. Forfeit\n";
        int choice = Utils::readInt("Choose: ", 1, 7);
        if (choice == 1)
        {
            int power = mine.getMove(0).getPower();
            int damage = mine.damageAgainst(foe, power);
            int before = foe.getHp();
            foe -= damage;
            std::cout << "\n - " << mine.getName() << " uses " << mine.getMove(0).getName() << " on " << foe.getName() << " for " << before - foe.getHp() << " damage!\n";
            acted = true;
        }
        if (choice == 2)
        {
            if (mine.getMove(1).isReady())
            {
                int power = mine.getMove(1).getPower();
                int damage = mine.damageAgainst(foe, power);
                int before = foe.getHp();
                foe -= damage;
                mine.getMove(1).use();
                std::cout << "\n - " << mine.getName() << " uses " << mine.getMove(1).getName() << " on " << foe.getName() << " for " << before - foe.getHp() << " damage!\n";
                acted = true;
            }
            else
            {
                std::cout << "\n - " << "Special is still under cooldown!\n";
            }
        }
        if (choice == 3)
        {
            mine.defend();
            std::cout << "\n - " << mine.getName() << " braces for the next hit!\n";
            acted = true;
        }
        if (choice == 4)
        {
            if (playerHealsLeft > 0)
            {
                int before = mine.getHp();
                mine.heal(30);
                playerHealsLeft--;
                std::cout << "\n - " << mine.getName() << " heals with " << mine.getHp() - before << " HP \n";
                acted = true;
            }
            else
            {
                std::cout << "\n - " << "No heals left!\n";
            }
        }
        if (choice == 5)
        {
            for (int i = 0; i < player.getCount(); i++)
            {
                const Dragon &d = player.getDragon(i);
                std::cout << i + 1 << ". " << d.getName() << " " << d.getHp() << "/" << d.getMaxHp();
                if (d.isFainted())
                {
                    std::cout << " (fainted)";
                }
                std::cout << "\n";
            }
            int pick = Utils::readInt("Switch to: ", 1, player.getCount()) - 1;
            if (pick == playerActive)
            {
                std::cout << "Already Fighting!\n";
            }
            else if (player.getDragon(pick).isFainted())
            {
                std::cout << "The Dragon has fainted!\n";
            }
            else
            {
                playerActive = pick;
                std::cout << "\n - " << "The player has picked " << player.getDragon(pick).getName() << '\n';
                acted = true;
            }
        }
        if (choice == 6)
        {
            std::cout << "\n--- Your dragon ---\n";
            showStats(mine);
            std::cout << "\n--- Enemy dragon ---\n";
            showStats(foe);
            std::cout << "\n";
        }
        if (choice == 7)
        {
            std::cout << player.getName() << " forfeits the battle!\n";
            return false;
        }
    }
    return true;
}

void Battle::enemyTurn()
{
    std::cout << "# Enemy's Turn\n";
    Dragon &mine = enemy.getDragon(enemyActive);
    Dragon &foe = player.getDragon(playerActive);
    int roll = rand() % 100 + 1;
    bool attacking = false;

    if (roll <= 70)
    {
        attacking = true;
    }
    else if (roll <= 90)
    {
        mine.defend();
        std::cout << " - " << mine.getName() << " braces for the next hit!\n";
    }
    else
    {
        if (enemyHealsLeft > 0 && mine.getHp() < mine.getMaxHp() / 2)
        {
            int before = mine.getHp();
            mine.heal(30);
            enemyHealsLeft--;
            std::cout << " - " << mine.getName() << " heals with " << mine.getHp() - before << " HP \n";
        }
        else
        {
            attacking = true;
        }
    }

    if (attacking)
    {
        int power = mine.getMove(0).getPower();
        int damage = mine.damageAgainst(foe, power);
        int before = foe.getHp();
        foe -= damage;
        std::cout << " - " << mine.getName() << " uses " << mine.getMove(0).getName() << " on " << foe.getName() << " for " << before - foe.getHp() << " damage!\n";
    }
}

void Battle::switchIfFainted(Player &who, int &active)
{
    if (!who.getDragon(active).isFainted())
    {
        return;
    }
    int next = who.firstLivingIndex();
    if (next != -1)
    {   
        std::cout << "\n - " << who.getDragon(active).getName() << " fainted!\n";
        active = next;
        std::cout << " - " << who.getDragon(next).getName() << " enters the battle arena!\n\n";
    }
}

bool Battle::run()
{
    while (player.hasLivingDragon() && enemy.hasLivingDragon())
    {
        showStatus();
        player.getDragon(playerActive).endTurn();
        if (!playerTurn())
        {
            return false;
        }
        switchIfFainted(enemy, enemyActive);
        if (!enemy.hasLivingDragon())
        {
            break;
        }
        enemy.getDragon(enemyActive).endTurn();
        enemyTurn();
        switchIfFainted(player, playerActive);
        if (!player.hasLivingDragon())
        {
            break;
        }
        turn++;
    }
    return player.hasLivingDragon();
}
