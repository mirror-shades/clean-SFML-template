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
    std::vector<Monster> &getActiveMonsters();
    Monster &getActiveMonster(size_t index);
    void setActiveMonster(size_t index);
    Monster &getActiveMonster();
    int getSteps() const;
    void setSteps(int newSteps);
    void updateActiveMonsters(std::vector<Monster> newMonsters);

private:
    int x = 0;
    int y = 0;
    int steps = 100;
    std::vector<Monster> activeMonsters;
    size_t activeMonster = 0;
};
