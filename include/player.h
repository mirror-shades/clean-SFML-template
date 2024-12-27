#pragma once

#include <vector>
#include <utility>
#include "monster.h"
#include "monsterManager.h"
#include "moves.h"

class Player
{
public:
    void setPosition(int newX, int newY);
    std::pair<int, int> getPosition() const;
    void addMonster(int type, MonsterManager &monsterManager);
    const std::vector<Monster> &getActiveMonsters() const;
    Monster &getActiveMonster(size_t index);
    void setActiveMonster(size_t index);
    Monster getActiveMonster() const;
    int getSteps() const;
    void setSteps(int newSteps);

private:
    int x = 0;
    int y = 0;
    int steps = 100;
    std::vector<Monster> activeMonsters;
    size_t activeMonster = 0;
};
