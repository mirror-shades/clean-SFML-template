#pragma once

#include <SFML/Graphics.hpp>
#include "map.h"
#include "player.h"
#include "monsterManager.h"
#include "environment.h"

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
    void checkGrass(MapHandler &map, Player &player, Environment &environment, MonsterManager &monsterManager);
    void setState(gameState newState, Player &player);
    bool movePlayer(sf::Event event, Player &player, MapHandler &map);
    void battleTick(Player &player, Environment &environment);
    void determineTurnOrder(std::vector<Monster> &monsters);
    void executeAIMove(Monster &attacker, std::vector<Monster> &targets);
    void executePlayerMove(Monster &attacker, Monster &target, int moveIndex);
    int calculateMoveDamage(const Monster &attacker, const Monster &target, const Move &move);
    void checkIfMonsterDies(std::vector<Monster> &playerMonsters, std::vector<Monster> &enemyMonsters);

private:
    gameState state = GAME_MAIN_MENU;
};