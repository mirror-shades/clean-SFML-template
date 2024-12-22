#pragma once
#include "map.h"
#include "player.h"

enum gameState
{
    GAME_OVER,
    GAME_RUNNING,
    GAME_PAUSED,
    GAME_MENU,
    GAME_MONSTER_ENCOUNTERED
};

struct Environment
{
    std::vector<Monster> enemyMonsters;
};

class Engine
{
public:
    gameState state;
    void update(Map &map, Player &player, Environment &environment, MonsterManager &monsterManager);
};