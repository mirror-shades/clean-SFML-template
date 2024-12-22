#include <SFML/Graphics.hpp>
#include "render.h"
#include "map.h"
#include "player.h"
#include "engine.h"
#include "menu.h"

sf::Font font;

void Render::loadFont()
{
    if (!font.loadFromFile("assets/Consolas.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
}

void Render::drawBackground(sf::RenderWindow &window)
{
    sf::RectangleShape background(sf::Vector2f(1200, 800));
    background.setFillColor(sf::Color::Black);
    window.draw(background);
}

void Render::drawPlayer(sf::RenderWindow &window, Player &player)
{
    drawSymbol(window, '@', player.x, player.y);
}

void Render::drawSymbol(sf::RenderWindow &window, const char symbol, int x, int y)
{
    sf::Text text(symbol, font);
    int offset = 0;
    if (symbol == '"')
        offset = 14; // move grass down a quarter of the square size
    text.setCharacterSize(Map::SQUARE_SIZE);
    text.setPosition(x * Map::SQUARE_SIZE, y * Map::SQUARE_SIZE + offset);
    window.draw(text);
}

void Render::drawTile(sf::RenderWindow &window, const Tile &tile, int x, int y)
{
    // Draw background
    sf::RectangleShape background(sf::Vector2f(Map::SQUARE_SIZE, Map::SQUARE_SIZE));
    // this magic is needed to convert the color from 0xRRGGBB to sf::Color for SFML
    // this format is a split hex value, (0x00, 0x00, 0x00) for black, ect
    const sf::Color squareColor = sf::Color(
        (static_cast<int>(tile.color) >> 5) * 32,         // Red   (bits 5-7)
        ((static_cast<int>(tile.color) >> 2) & 0x7) * 32, // Green (bits 2-4)
        (static_cast<int>(tile.color) & 0x3) * 64         // Blue  (bits 0-1)
    );
    background.setFillColor(squareColor);
    background.setPosition(x * Map::SQUARE_SIZE, y * Map::SQUARE_SIZE);
    window.draw(background);
    this->drawSymbol(window, tile.symbol, x, y);
}

void Render::drawScreen(sf::RenderWindow &window, Engine &engine, Map &map, Player &player)
{
    if (engine.state == GAME_MENU)
    {
        drawMenu(window);
    }
    if (engine.state == GAME_RUNNING)
    {
        drawMap(window, map);
        drawPlayer(window, player);
    }
}

void Render::drawMenu(sf::RenderWindow &window)
{
    sf::Text text("Menu", font);
    text.setCharacterSize(Map::SQUARE_SIZE);
    text.setPosition(0, 0);
    window.draw(text);
}

void Render::drawMap(sf::RenderWindow &window, const Map &map)
{
    drawBackground(window);
    for (int j = 0; j < Map::MAP_HEIGHT; j++)
    {
        for (int i = 0; i < Map::MAP_WIDTH; i++)
        {
            drawTile(window, map.currentMap[i][j], i, j);
        }
    }
}