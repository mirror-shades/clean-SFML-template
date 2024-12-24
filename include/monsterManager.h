#pragma once

#include "monster.h"

class MonsterManager
{
public:
    Monster createMonster(int type);
    void initializeMonsterTypes();
    void printMonster(Monster monster);
    void initializeMoveTypes();
};