#pragma once

#include <SFML/Graphics.hpp>
#include "tile.h"
#include "map.h"
#include "player.h"
#include "engine.h"

class Render
{
public:
    void loadFont();
    void drawPlayer(sf::RenderWindow &window, Player &player);
    void drawScreen(sf::RenderWindow &window, Engine &engine, Map &map, Player &player);

private:
    void drawBackground(sf::RenderWindow &window);
    void drawMap(sf::RenderWindow &window, const Map &map);
    void drawTile(sf::RenderWindow &window, const Tile &tile, int x, int y);
    void drawSymbol(sf::RenderWindow &window, char symbol, int x, int y);
};
