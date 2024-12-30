#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "tile.h"
#include "map.h"
#include "player.h"
#include "engine.h"

class Render
{
public:
    int selection;
    std::vector<std::string> options;
    void loadFont();
    void drawPlayer(sf::RenderWindow &window, Player &player);
    void drawScreen(sf::RenderWindow &window, Engine &engine, MapHandler &map, Player &player, MonsterManager &monsterManager, Environment &environment, int selection);
    void drawBattle(sf::RenderWindow &window, Player &player, MonsterManager &monsterManager, Engine &engine, Environment &environment, int &selection);
    void drawTestBattle(sf::RenderWindow &window, Player &player, MonsterManager &monsterManager, Engine &engine, Environment &environment, int &selection);
    void drawLevelSelect(sf::RenderWindow &window, Engine &engine, int &selection);
    void drawAttackMenu(sf::RenderWindow &window, Engine &engine, int &selection, int screenWidth, int screenHeight);

private:
    void drawBackground(sf::RenderWindow &window);
    void drawMap(sf::RenderWindow &window, const MapHandler &map);
    void drawTile(sf::RenderWindow &window, const Tile &tile, int x, int y);
    void drawSymbol(sf::RenderWindow &window, char symbol, int x, int y);
    void drawMenu(sf::RenderWindow &window, Engine &engine, int &selection);
    void drawOverlay(sf::RenderWindow &window, Environment &environment, Player &player);
};
