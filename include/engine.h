#pragma once

#include <SFML/Graphics.hpp>
#include "map.h"
#include "player.h"
#include "monsterManager.h"
#include "environment.h"
#include "battle.h"

enum gameState
{
    GAME_OVER,
    GAME_RUNNING,
    GAME_MAIN_MENU,
    GAME_LEVEL_SELECT,
    GAME_MONSTER_ENCOUNTERED
};

class Engine
{
public:
    std::vector<std::string> menuOptions;
    gameState getState();
    void checkGrass(MapHandler &map, Player &player, Environment &environment, MonsterManager &monsterManager, Battle &battle);
    void setState(gameState newState, Player &player);
    bool movePlayer(sf::Event event, Player &player, MapHandler &map);
    void battleTick(Player &player, Environment &environment, Battle &battle);
    void determineTurnOrder(std::vector<Monster> &monsters);
    void checkIfMonsterDies(std::vector<Monster> &playerBattleMonsters, std::vector<Monster> &enemyBattleMonsters, Environment &environment, Player &player, Battle &battle);

private:
    gameState state = GAME_MAIN_MENU;
};