#pragma once

#include <vector>
#include <utility>
#include "monster.h"

class Player
{
private:
    int x = 0;
    int y = 0;
    std::vector<Monster> activeMonsters;

public:
    void setPosition(int newX, int newY);
    std::pair<int, int> getPosition() const;
    void addMonster(int type, MonsterManager &monsterManager);
    const std::vector<Monster> &getActiveMonsters() const;
    Monster &getActiveMonster(size_t index);
};
