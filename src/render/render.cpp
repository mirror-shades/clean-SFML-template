#include <SFML/Graphics.hpp>
#include "render.h"
#include "map.h"
#include "player.h"
#include "elements.h"
#include <iostream>
#include <cmath>

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

void Render::drawScreen(int state, int selection, std::vector<std::string> menuOptions)
{
    if (state == 1)
    {
        drawMenu(*window, selection, menuOptions);
    }
    if (state == 2)
    {
        drawMap(*window, *map);
        drawPlayer(*window, *player);
        drawOverlay(*window, *environment, *player);
    }
    if (state == 3)
    {
        drawLevelSelect(*window, selection, menuOptions);
    }
    if (state == 4)
    {
        drawBattle(*window, *player, *environment, selection, *battle, menuOptions);
    }
}

void Render::drawLevelSelect(sf::RenderWindow &window, int &selection, std::vector<std::string> menuOptions)
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
    rectangle.setFillColor(sf::Color(0, 0, 0, 75)); // Black with 50% opacity (alpha=128)
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

bool Render::isAnimating()
{
    return !animationQueue.empty();
}

void Render::queueAnimation(AnimationState state, int source, int target, float duration)
{
    BattleAnimation anim = {state, source, target, duration, 0.0f};
    animationQueue.push_back(anim);
}

void Render::updateAnimation(float deltaTime)
{
    if (!animationQueue.empty())
    {
        animationQueue[0].elapsed += deltaTime;
        if (animationQueue[0].elapsed >= animationQueue[0].duration)
        {
            animationQueue.erase(animationQueue.begin());
        }
    }
}

BattleAnimation *Render::getCurrentAnimation()
{
    return animationQueue.empty() ? nullptr : &animationQueue[0];
}

void Render::drawBattle(sf::RenderWindow &window, Player &player, Environment &environment, int &selection, Battle &battle, std::vector<std::string> menuOptions)
{
    int screenWidth = MAP_WIDTH * SQUARE_SIZE;
    int screenHeight = MAP_HEIGHT * SQUARE_SIZE;

    std::vector<sf::Vector2f> leftPositions = {
        sf::Vector2f(screenWidth * 0.15f, screenHeight * 0.2f),
        sf::Vector2f(screenWidth * 0.25f, screenHeight * 0.4f),
        sf::Vector2f(screenWidth * 0.15f, screenHeight * 0.6f)};

    std::vector<sf::Vector2f> rightPositions = {
        sf::Vector2f(screenWidth * 0.85f, screenHeight * 0.2f),
        sf::Vector2f(screenWidth * 0.75f, screenHeight * 0.4f),
        sf::Vector2f(screenWidth * 0.85f, screenHeight * 0.6f)};

    // Test animation (you can remove this later)
    static bool animationAdded = false;
    if (!animationAdded && animationQueue.empty())
    {
        queueAnimation(ATTACKING, 0, 0, 1.0f); // 1 second attack
        queueAnimation(DEFENDING, 0, 0, 1.0f); // 1 second defend
        animationAdded = true;
    }

    BattleAnimation *currentAnim = getCurrentAnimation();
    if (currentAnim)
    {
        drawBattleWithAnimation(window, *currentAnim, leftPositions, rightPositions);
    }

    // Helper function to draw resource bars
    auto drawResourceBars = [&](float x, float y, Monster &monster)
    {
        const float MOVE_THRESHOLD_MULTIPLIER = 10.0f;
        const float BAR_WIDTH = 60.0f;
        const float BAR_HEIGHT = 5.0f;
        const float BAR_SPACING = 2.0f;
        ;
        // HP Bar (Green)
        sf::RectangleShape hpBar(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
        hpBar.setFillColor(sf::Color::Green);
        hpBar.setPosition(x - BAR_WIDTH / 2, y);
        float hpRatio = static_cast<float>(monster.currentStats.health) / monster.baseStats.health;
        hpBar.setScale(hpRatio, 1.0f);
        window.draw(hpBar);

        // MP Bar (Blue)
        sf::RectangleShape mpBar(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
        mpBar.setFillColor(sf::Color::Blue);
        mpBar.setPosition(x - BAR_WIDTH / 2, y + BAR_HEIGHT + BAR_SPACING);
        mpBar.setScale(static_cast<float>(monster.movePoints) /
                           (monster.currentStats.specialAttack * MOVE_THRESHOLD_MULTIPLIER),
                       1.0f);
        window.draw(mpBar);

        // TP Bar (Yellow)
        sf::RectangleShape tpBar(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
        tpBar.setFillColor(sf::Color::Yellow);
        tpBar.setPosition(x - BAR_WIDTH / 2, y + (BAR_HEIGHT + BAR_SPACING) * 2);
        tpBar.setScale(static_cast<float>(monster.turnPoints) / 100, 1.0f);
        window.draw(tpBar);
    };

    // Draw player monsters
    for (size_t i = 0; i < player.getActiveMonsters().size() && i < leftPositions.size(); i++)
    {
        sf::Texture texture;
        sf::Sprite sprite;
        std::string imagePath = "assets/images/" + player.getActiveMonsters()[i].baseStats.name + ".png";

        if (texture.loadFromFile(imagePath))
        {
            sprite.setTexture(texture);
            sprite.setScale(0.2f, 0.2f);
            sprite.setPosition(
                leftPositions[i].x - (sprite.getLocalBounds().width * 0.2f) / 2,
                leftPositions[i].y - (sprite.getLocalBounds().height * 0.2f) / 2);

            // Set opacity based on monster health
            sf::Color spriteColor = sf::Color::White;
            if (player.getActiveMonsters()[i].currentStats.health <= 0)
            {
                spriteColor.a = 75; // 50% opacity for defeated monsters
            }
            sprite.setColor(spriteColor);
            window.draw(sprite);

            // Draw resource bars below the sprite
            float barY = leftPositions[i].y + (sprite.getLocalBounds().height * 0.2f) / 2 + 5;
            drawResourceBars(leftPositions[i].x, barY, player.getActiveMonsters()[i]);
        }
    }

    // Draw enemy monsters
    for (size_t i = 0; i < environment.getEnemyMonsters().size() && i < rightPositions.size(); i++)
    {
        sf::Texture texture;
        sf::Sprite sprite;
        std::string imagePath = "assets/images/" + environment.getEnemyMonsters()[i].baseStats.name + ".png";

        if (texture.loadFromFile(imagePath))
        {
            sprite.setTexture(texture);
            sprite.setScale(-0.2f, 0.2f);
            sprite.setPosition(
                rightPositions[i].x + (sprite.getLocalBounds().width * 0.2f) / 2,
                rightPositions[i].y - (sprite.getLocalBounds().height * 0.2f) / 2);

            // Set opacity based on monster health
            sf::Color spriteColor = sf::Color::White;
            if (environment.getEnemyMonsters()[i].currentStats.health <= 0)
            {
                spriteColor.a = 75; // 50% opacity for defeated monsters
            }
            sprite.setColor(spriteColor);
            window.draw(sprite);

            // Draw resource bars below the sprite
            float barY = rightPositions[i].y + (sprite.getLocalBounds().height * 0.2f) / 2 + 5;
            drawResourceBars(rightPositions[i].x, barY, environment.getEnemyMonsters()[i]);
        }
    }

    if (true) // change this to a method to see if it's your monster's turn
    {
        drawAttackMenu(window, selection, screenWidth, screenHeight, menuOptions);
    }
}

void Render::drawAttackMenu(sf::RenderWindow &window, int &selection, int screenWidth, int screenHeight, std::vector<std::string> menuOptions)
{
    std::string move1 = menuOptions[0];
    std::string move2 = menuOptions[1];
    std::string move3 = menuOptions[2];
    std::string switchMonster = menuOptions[3];

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

void Render::drawMenu(sf::RenderWindow &window, int &selection, std::vector<std::string> menuOptions)
{
    const int SPACING = SQUARE_SIZE * 2; // Space between options
    const int START_X = 200;             // Starting X position
    const int START_Y = 200;             // Y position for all options

    for (size_t i = 0; i < menuOptions.size(); i++)
    {
        sf::Text text(menuOptions[i], font);
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

void Render::drawBattleWithAnimation(sf::RenderWindow &window, const BattleAnimation &anim,
                                     std::vector<sf::Vector2f> &leftPositions,
                                     std::vector<sf::Vector2f> &rightPositions)
{
    // Apply different visual effects based on animation state
    switch (anim.state)
    {
    case ATTACKING:
        // Move the attacking monster forward
        if (anim.sourceIndex < leftPositions.size())
        {
            leftPositions[anim.sourceIndex].x += 50.0f * sin(anim.elapsed * 3.14159f);
        }
        break;

    case DEFENDING:
        // Make the defending monster bounce
        if (anim.targetIndex < rightPositions.size())
        {
            rightPositions[anim.targetIndex].y += 20.0f * sin(anim.elapsed * 6.28318f);
        }
        break;

    default:
        break;
    }
}

void Render::setReferences(sf::RenderWindow &w, MapHandler &m, Player &p,
                           MonsterManager &mm, Environment &env, Battle &b)
{
    window = &w;
    map = &m;
    player = &p;
    monsterManager = &mm;
    environment = &env;
    battle = &b;
}