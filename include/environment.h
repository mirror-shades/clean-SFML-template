#pragma once
#include <string>
#include <vector>
#include "monster.h"
#include "elements.h"

struct Environment
{
    std::vector<Monster> enemyMonsters;
    void determineLevelElement(ElementType levelElement);
    ElementType getLevelElement();
    std::string getLevelElementString();

private:
    ElementType levelElement;
};