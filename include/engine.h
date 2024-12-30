#pragma once

#include <SFML/Graphics.hpp>
#include "map.h"
#include "player.h"
#include "monsterManager.h"
#include "environment.h"
#include "battle.h"
#include "render.h"

class Engine
{
public:
    bool movePlayer(sf::Event event, Player &player, MapHandler &map);
    void battleTick(Player &player, Environment &environment, Battle &battle);
    void determineTurnOrder(std::vector<Monster> &monsters);
    void checkIfMonsterDies(std::vector<Monster> &playerBattleMonsters, std::vector<Monster> &enemyBattleMonsters, Environment &environment, Player &player, Battle &battle);
    bool checkGrass(MapHandler &map, Player &player, Environment &environment, MonsterManager &monsterManager, Battle &battle, int state);
};