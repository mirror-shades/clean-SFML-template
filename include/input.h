#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"
#include "map.h"
#include "engine.h"
#include "monsterManager.h"

class InputManager
{
public:
    bool handleInput(sf::Event event, Player &player, MonsterManager &monsterManager, Map &map, Engine &engine, int &selection);
    bool movePlayer(sf::Event event, Player &player, Map &map);
    bool moveMenu(sf::Event event, int &selection, std::vector<std::string> options);
    int updateSelection(int options, int change, int &selection);
    void handleMenuSelection(std::string selection, Player &player, MonsterManager &monsterManager);
    bool handleBattleInput(sf::Event event, int &selection, Player &player, Engine &engine);
};