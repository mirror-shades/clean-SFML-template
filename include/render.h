#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "tile.h"
#include "map.h"
#include "player.h"
#include "engine.h"
#include "menu.h"

class Render
{
public:
    void loadFont();
    void drawPlayer(sf::RenderWindow &window, Player &player);
    void drawScreen(sf::RenderWindow &window, Engine &engine, Map &map, Player &player, Menu &menu, std::vector<std::string> options);

private:
    void drawBackground(sf::RenderWindow &window);
    void drawMap(sf::RenderWindow &window, const Map &map);
    void drawTile(sf::RenderWindow &window, const Tile &tile, int x, int y);
    void drawSymbol(sf::RenderWindow &window, char symbol, int x, int y);
    void drawMenu(sf::RenderWindow &window, Menu &menu, std::vector<std::string> options);
};
