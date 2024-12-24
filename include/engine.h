#pragma once
#include "map.h"
#include "player.h"
#include "monsterManager.h"

enum gameState
{
    GAME_OVER,
    GAME_RUNNING,
    GAME_PAUSED,
    GAME_MAIN_MENU,
    GAME_MONSTER_ENCOUNTERED
};

struct Environment
{
    std::vector<Monster> enemyMonsters;
};

class Engine
{
public:
    std::vector<std::string> menuOptions;
    gameState getState();
    void checkGrass(MapHandler &map, Player &player, Environment &environment, MonsterManager &monsterManager);
    void setState(gameState newState, Player &player);

private:
    gameState state = GAME_MAIN_MENU;
};