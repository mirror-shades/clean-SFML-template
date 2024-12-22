#include <vector>
#include <utility>
#include <iostream>
#include "player.h"
#include "monster.h"

Player player = {0, 0};
std::vector<Monster> activeMonsters;

Player &PlayerManager::getPlayer() { return player; }

void PlayerManager::setPlayerPosition(int x, int y)
{
    player.x = x;
    player.y = y;
}

std::pair<int, int> PlayerManager::getPlayerPosition()
{
    return {player.x, player.y};
}

void PlayerManager::addMonster(int type, MonsterManager &monsterManager)
{
    std::cout << "Adding monster type " << type << " at line " << __LINE__ << std::endl;
    activeMonsters.push_back(monsterManager.createMonster(type));
}

std::vector<Monster> PlayerManager::getActiveMonsters()
{
    return activeMonsters;
}
