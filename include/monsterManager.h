#pragma once

#include "monster.h"
#include <vector>

class MonsterManager
{
public:
    Monster createMonster(int type, Faction faction);
    void initializeMonsterTypes();
    void printMonster(Monster monster);
    void initializeMoveTypes();
    int totalMonsters;

private:
    std::vector<Monster> monsters; // Store monsters here to return references to them
};