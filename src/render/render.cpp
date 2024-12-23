#include <SFML/Graphics.hpp>
#include "render.h"
#include "map.h"
#include "player.h"
#include "engine.h"

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
    drawSymbol(window, '@', player.getPosition().first, player.getPosition().second);
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

void Render::drawScreen(sf::RenderWindow &window, Engine &engine, Map &map, Player &player, MonsterManager &monsterManager, Environment &environment, std::vector<std::string> options, int selection)
{
    if (engine.state == GAME_MENU)
    {
        drawMenu(window, options, selection);
    }
    if (engine.state == GAME_RUNNING)
    {
        drawMap(window, map);
        drawPlayer(window, player);
    }
    if (engine.state == GAME_MONSTER_ENCOUNTERED)
    {
        drawBattle(window, player, monsterManager, environment);
    }
}

void Render::drawBattle(sf::RenderWindow &window, Player &player, MonsterManager &monsterManager, Environment &environment)
{
    // just write the name of the most recent monster in the enviroment to the screen
    sf::Text text(environment.enemyMonsters.back().name, font);
    text.setCharacterSize(Map::SQUARE_SIZE);
    text.setPosition(100, 100);
    window.draw(text);

    std::vector<Monster> activeMonsters = player.getActiveMonsters();
    sf::Text text2(activeMonsters.back().name, font);
    text2.setCharacterSize(Map::SQUARE_SIZE);
    text2.setPosition(100, 200);
    window.draw(text2);
}

void Render::drawMenu(sf::RenderWindow &window, std::vector<std::string> options, int &selection)
{
    const int SPACING = Map::SQUARE_SIZE * 2; // Space between options
    const int START_X = 100;                  // Starting X position
    const int START_Y = 100;                  // Y position for all options

    for (size_t i = 0; i < options.size(); i++)
    {
        sf::Text text(options[i], font);
        text.setCharacterSize(Map::SQUARE_SIZE);
        text.setPosition(START_X, START_Y + (i * SPACING));

        // Highlight the current selection
        if (i == selection)
        {
            text.setFillColor(sf::Color::Yellow); // Or any highlight color you prefer
        }
        else
        {
            text.setFillColor(sf::Color::White);
        }

        window.draw(text);
    }
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