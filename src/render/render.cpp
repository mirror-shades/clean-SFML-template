#include <SFML/Graphics.hpp>
#include "render.h"
#include "map.h"
#include "player.h"
#include "engine.h"
#include "elements.h"
#include <iostream>

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
    text.setCharacterSize(SQUARE_SIZE);
    text.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE + offset);
    window.draw(text);
}

void Render::drawTile(sf::RenderWindow &window, const Tile &tile, int x, int y)
{
    // Draw background
    sf::RectangleShape background(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    // this magic is needed to convert the color from 0xRRGGBB to sf::Color for SFML
    // this format is a split hex value, (0x00, 0x00, 0x00) for black, ect
    const sf::Color squareColor = sf::Color(
        (static_cast<int>(tile.color) >> 5) * 32,         // Red   (bits 5-7)
        ((static_cast<int>(tile.color) >> 2) & 0x7) * 32, // Green (bits 2-4)
        (static_cast<int>(tile.color) & 0x3) * 64         // Blue  (bits 0-1)
    );
    char symbolToDraw = tile.symbol;
    if (tile.symbol == 'g')
    {
        symbolToDraw = '"';
    }
    background.setFillColor(squareColor);
    background.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE);
    window.draw(background);
    this->drawSymbol(window, symbolToDraw, x, y);
}

void Render::drawScreen(sf::RenderWindow &window, Engine &engine, MapHandler &map, Player &player, MonsterManager &monsterManager, Environment &environment, int selection)
{

    if (engine.getState() == GAME_MAIN_MENU)
    {
        drawMenu(window, engine, selection);
    }
    if (engine.getState() == GAME_RUNNING)
    {
        drawMap(window, map);
        drawPlayer(window, player);
        drawOverlay(window, environment, player);
    }
    if (engine.getState() == GAME_MONSTER_ENCOUNTERED)
    {
        drawBattle(window, player, monsterManager, engine, environment, selection);
    }
    if (engine.getState() == GAME_LEVEL_SELECT)
    {
        drawLevelSelect(window, engine, selection);
    }
}

void Render::drawLevelSelect(sf::RenderWindow &window, Engine &engine, int &selection)
{
    std::map<int, sf::Color> elementToColor = {
        {ElementType::EARTH, sf::Color(34, 139, 34)},      // Forest Green
        {ElementType::WATER, sf::Color(0, 105, 148)},      // Deep Ocean Blue
        {ElementType::FIRE, sf::Color(255, 69, 0)},        // Red-Orange
        {ElementType::AIR, sf::Color(135, 206, 235)},      // Sky Blue
        {ElementType::DIVINE, sf::Color(255, 215, 0)},     // Golden
        {ElementType::DEMONIC, sf::Color(139, 0, 0)},      // Dark Red
        {ElementType::PSYCHIC, sf::Color(147, 112, 219)},  // Purple
        {ElementType::ELECTRIC, sf::Color(255, 255, 0)},   // Bright Yellow
        {ElementType::ELDRITCH, sf::Color(75, 0, 130)},    // Indigo
        {ElementType::FIGHTING, sf::Color(165, 42, 42)},   // Brown
        {ElementType::CYBERNETIC, sf::Color(0, 191, 255)}, // Deep Sky Blue
        {ElementType::DRAGON, sf::Color(148, 0, 211)}};    // Dark Violet

    std::map<ElementType, std::string> elementToName = {
        {ElementType::PSYCHIC, "PSYCHIC"},
        {ElementType::DRAGON, "DRAGON"},
        {ElementType::FIRE, "FIRE"}};

    std::vector<ElementType> levelOptions = {ElementType::PSYCHIC, ElementType::DRAGON, ElementType::FIRE};

    const int SPACING = SQUARE_SIZE * 2; // Space between options
    const int START_X = 200;             // Starting X position
    const int START_Y = 200;             // Y position for all options
    const int SQUARE_OFFSET = 50;        // Offset for the selection square

    // Draw selection square if this option is selected
    sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    square.setFillColor(sf::Color::White);
    square.setPosition(START_X - SQUARE_OFFSET, START_Y + (selection * SPACING));
    window.draw(square);

    // 2 squared to the right of the selection square
    // draw a square of a random color
    // these should always be visible, so draw 3 of them
    for (int i = 0; i < 3; i++)
    {
        sf::RectangleShape randomSquare(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
        randomSquare.setFillColor(elementToColor[levelOptions[i]]);
        randomSquare.setPosition(START_X + SQUARE_SIZE * 2, START_Y + (i * SPACING));
        window.draw(randomSquare);

        std::string elementName = elementToName[levelOptions[i]];
        sf::Text text(elementName, font);
        text.setCharacterSize(SQUARE_SIZE / 2);
        text.setPosition(START_X + SQUARE_SIZE * 3 + 8, START_Y + (i * SPACING) + 8);
        window.draw(text);
    }
}

void Render::drawOverlay(sf::RenderWindow &window, Environment &environment, Player &player)
{
    // make a rectangle over the top right 3 squares
    sf::RectangleShape rectangle(sf::Vector2f(SQUARE_SIZE * 5, SQUARE_SIZE * 1));
    rectangle.setFillColor(sf::Color(0, 0, 0, 128)); // Black with 50% opacity (alpha=128)
    rectangle.setPosition(MAP_WIDTH * SQUARE_SIZE - SQUARE_SIZE * 4, 0);
    window.draw(rectangle);
    // write a word in the top right corner
    sf::Text text(environment.getLevelElementString(), font);
    text.setCharacterSize(SQUARE_SIZE / 2);
    text.setPosition(MAP_WIDTH * SQUARE_SIZE - SQUARE_SIZE * 3.5, 10);
    window.draw(text);
    // write a number in the top right corner
    sf::Text text2(std::to_string(player.getSteps()), font);
    text2.setCharacterSize(SQUARE_SIZE / 2);
    text2.setPosition(MAP_WIDTH * SQUARE_SIZE - SQUARE_SIZE, 10);
    window.draw(text2);
}

void Render::drawBattle(sf::RenderWindow &window, Player &player, MonsterManager &monsterManager, Engine &engine, Environment &environment, int &selection)
{
    int screenWidth = MAP_WIDTH * SQUARE_SIZE;
    int screenHeight = MAP_HEIGHT * SQUARE_SIZE;

    // Add player monster sprite drawing
    sf::Texture playerMonsterTexture;
    sf::Sprite playerMonsterSprite;
    std::string playerMonsterName = player.getActiveMonster().name;
    std::string playerMonsterImagePath = "assets/images/" + playerMonsterName + ".png";

    if (playerMonsterTexture.loadFromFile(playerMonsterImagePath))
    {
        playerMonsterSprite.setTexture(playerMonsterTexture);
        // Scale down by 50%
        playerMonsterSprite.setScale(0.5f, 0.5f);
        // Position the monster on the center left side
        playerMonsterSprite.setPosition(
            screenWidth / 4 - (playerMonsterSprite.getLocalBounds().width * 0.5f) / 2,
            screenHeight * 1 / 3 - (playerMonsterSprite.getLocalBounds().height * 0.5f) / 2);
        window.draw(playerMonsterSprite);
    }

    // Add enemy monster sprite drawing
    sf::Texture enemyMonsterTexture;
    sf::Sprite enemyMonsterSprite;
    std::string enemyMonsterName = environment.enemyMonsters.back().name;
    std::string enemyMonsterImagePath = "assets/images/" + enemyMonsterName + ".png";

    if (enemyMonsterTexture.loadFromFile(enemyMonsterImagePath))
    {
        enemyMonsterSprite.setTexture(enemyMonsterTexture);
        // Scale down by 50%
        enemyMonsterSprite.setScale(-0.5f, 0.5f); // Negative x scale to flip horizontally
        // Position the monster on the center right side
        enemyMonsterSprite.setPosition(
            screenWidth * 3 / 4 + (enemyMonsterSprite.getLocalBounds().width * 0.5f) / 2, // Adjusted for flipped sprite
            screenHeight * 1 / 3 - (enemyMonsterSprite.getLocalBounds().height * 0.5f) / 2);
        window.draw(enemyMonsterSprite);
    }

    std::string move1 = engine.menuOptions[0];
    std::string move2 = engine.menuOptions[1];
    std::string move3 = engine.menuOptions[2];
    std::string switchMonster = engine.menuOptions[3];

    sf::Text text(move1, font);
    text.setCharacterSize(SQUARE_SIZE);
    text.setPosition(screenWidth / 2 - text.getLocalBounds().width / 2,
                     screenHeight * 3 / 4 - SQUARE_SIZE * 2);
    if (selection == 0)
    {
        text.setFillColor(sf::Color::Yellow);
    }
    else
    {
        text.setFillColor(sf::Color::White);
    }
    window.draw(text);

    sf::Text text2(move2, font);
    text2.setCharacterSize(SQUARE_SIZE);
    text2.setPosition(screenWidth * 1 / 4 - text2.getLocalBounds().width / 2,
                      screenHeight * 3 / 4);
    if (selection == 1)
    {
        text2.setFillColor(sf::Color::Yellow);
    }
    else
    {
        text2.setFillColor(sf::Color::White);
    }
    window.draw(text2);

    sf::Text text3(move3, font);
    text3.setCharacterSize(SQUARE_SIZE);
    text3.setPosition(screenWidth * 3 / 4 - text3.getLocalBounds().width / 2,
                      screenHeight * 3 / 4);
    if (selection == 2)
    {
        text3.setFillColor(sf::Color::Yellow);
    }
    else
    {
        text3.setFillColor(sf::Color::White);
    }
    window.draw(text3);

    sf::Text text4(switchMonster, font);
    text4.setCharacterSize(SQUARE_SIZE);
    text4.setPosition(screenWidth / 2 - text4.getLocalBounds().width / 2,
                      screenHeight * 3 / 4 + SQUARE_SIZE);
    if (selection == 3)
    {
        text4.setFillColor(sf::Color::Yellow);
    }
    else
    {
        text4.setFillColor(sf::Color::White);
    }
    window.draw(text4);
}

void Render::drawMenu(sf::RenderWindow &window, Engine &engine, int &selection)
{
    const int SPACING = SQUARE_SIZE * 2; // Space between options
    const int START_X = 200;             // Starting X position
    const int START_Y = 200;             // Y position for all options

    for (size_t i = 0; i < engine.menuOptions.size(); i++)
    {
        sf::Text text(engine.menuOptions[i], font);
        text.setCharacterSize(SQUARE_SIZE);
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

void Render::drawMap(sf::RenderWindow &window, const MapHandler &map)
{
    drawBackground(window);
    for (int j = 0; j < MAP_HEIGHT; j++)
    {
        for (int i = 0; i < MAP_WIDTH; i++)
        {
            drawTile(window, map.getCurrentTile(i, j), i, j);
        }
    }
}