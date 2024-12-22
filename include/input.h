#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"
#include "map.h"
#include "menu.h"
#include "engine.h"
class InputManager
{
public:
    bool handleInput(sf::Event event, Player &player, PlayerManager &playerManager, Map &map, Engine &engine, Menu &menu, std::vector<std::string> options);
    bool movePlayer(sf::Event event, Player &player, PlayerManager &playerManager, Map &map);
    bool moveMenu(sf::Event event, Menu &menu, std::vector<std::string> options);
    int updateSelection(int options, int change, Menu &menu);
};