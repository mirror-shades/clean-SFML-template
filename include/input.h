#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
class InputManager
{
public:
    bool handleInput(sf::Event event, Player &player, PlayerManager &playerManager, Map &map);
    bool movePlayer(sf::Event event, Player &player, PlayerManager &playerManager, Map &map);
};