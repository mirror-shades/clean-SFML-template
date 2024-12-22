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

class Engine
{
public:
    gameState state;
    void update(Map &map, Player &player);
};