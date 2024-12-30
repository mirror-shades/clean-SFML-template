#pragma once
#include <string>
#include <vector>
#include "monster.h"
#include "elements.h"

struct Environment
{
    void determineLevelElement(ElementType levelElement);
    ElementType getLevelElement();
    std::string getLevelElementString();
    std::vector<Monster> &getEnemyMonsters();
    void addEnemyMonster(Monster monster);
    void removeEnemyMonster(Monster monster);
    void clearEnemyMonsters();
    void updateEnemyMonsters(std::vector<Monster> newMonsters);

private:
    std::vector<Monster> enemyMonsters;
    ElementType levelElement;
};