#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "player.h"
#include "map.h"
#include "engine.h"
#include "monsterManager.h"

class InputManager
{
public:
    std::pair<bool, bool> handleInput(sf::Event event, Player &player, MonsterManager &monsterManager, MapHandler &map, Engine &engine, Battle &battle, int &selection);
    bool moveMenu(sf::Event event, int &selection, std::vector<std::string> options);
    int updateSelection(int options, int change, int &selection);
    void handleMenuSelection(std::string selection, Player &player, MonsterManager &monsterManager);
    bool handleBattleInput(sf::Event event, int &selection, Player &player, Engine &engine, Battle &battle);
    bool handleLevelSelectInput(sf::Event event, int &selection, Engine &engine, Player &player);
};