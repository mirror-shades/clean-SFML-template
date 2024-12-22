#pragma once

#include "monster.h"

struct Player
{
    int x;
    int y;
};

class PlayerManager
{
public:
    Player &getPlayer();
    void addMonster(int type, MonsterManager &monsterManager);
    std::vector<Monster> getActiveMonsters();
    void setPlayerPosition(int x, int y);
    std::pair<int, int> getPlayerPosition();
};
