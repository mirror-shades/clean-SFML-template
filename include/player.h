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
    void addMonster(Monster monster);
    void setPlayerPosition(int x, int y);
    std::pair<int, int> getPlayerPosition();
};
