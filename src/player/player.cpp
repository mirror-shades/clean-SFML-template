#include "player.h"
#include <iostream>

void Player::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}

std::pair<int, int> Player::getPosition() const
{
    return {x, y};
}

void Player::addMonster(int type, MonsterManager &monsterManager)
{
    activeMonsters.push_back(monsterManager.createMonster(type));
}

std::vector<Monster> Player::getActiveMonsters()
{
    return activeMonsters;
}

int Player::getSteps() const
{
    return steps;
}

void Player::setSteps(int newSteps)
{
    steps = newSteps;
}

Monster Player::getActiveMonster(size_t index)
{
    return activeMonsters[index];
}

void Player::setActiveMonster(size_t index)
{
    activeMonster = index;
}

Monster Player::getActiveMonster()
{
    return activeMonsters[activeMonster];
}

void Player::updateActiveMonsters(std::vector<Monster> newMonsters)
{
    activeMonsters = newMonsters;
}
