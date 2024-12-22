#include <vector>
#include <utility>
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

void PlayerManager::addMonster(Monster monster)
{
    activeMonsters.push_back(monster);
}
