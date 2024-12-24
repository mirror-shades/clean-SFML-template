#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "render.h"
#include "tile.h"
#include "colors.h"
#include "engine.h"
#include "player.h"
#include "input.h"
#include "monster.h"

const std::string MAP_DATA[] = {
    "########################",
    "#                      #",
    "#                      #",
    "#                      #",
    "#          \"\"\"\"        #",
    "#          \"\"\"\"        #",
    "#          \"\"\"\"        #",
    "#          \"\"\"\"        #",
    "#                      #",
    "#                      #",
    "#                      #",
    "#                      #",
    "#                      #",
    "#                      #",
    "#                      #",
    "########################"};

// Convert string to tiles
void loadMapFromStrings(MapHandler &map, const std::string mapData[])
{
    Map newMap;
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            char c = mapData[y][x];
            bool walkable = (c == ' ' || c == '"');
            newMap.tiles[x][y] = Tile(c, Color::BLUE, walkable);
        }
    }
    map.setCurrentMap(newMap);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "");
    Render render;
    MapHandler map;
    Engine engine;
    Player player;
    InputManager inputManager;
    MonsterManager monsterManager;
    Environment environment;

    // Initialize monster types before creating any monsters
    monsterManager.initializeMoveTypes();
    monsterManager.initializeMonsterTypes();
    render.selection = 0;
    render.loadFont();

    loadMapFromStrings(map, MAP_DATA);
    bool needsUpdate = true;

    // Initialize player position
    player.setPosition(5, 5);

    // Set initial options based on game state
    engine.setState(GAME_MAIN_MENU, player);
    std::cout << "Menu size: " << engine.menuOptions.size() << std::endl;
    for (int i = 0; i < engine.menuOptions.size(); i++)
    {
        std::string option = engine.menuOptions[i];
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                needsUpdate = inputManager.handleInput(event, player, monsterManager, map, engine, render.selection);
            }
        }

        if (needsUpdate)
        {
            window.clear();
            engine.update(map, player, environment, monsterManager);
            render.drawScreen(window, engine, map, player, monsterManager, environment, render.selection);
            window.display();
            needsUpdate = false;
        }
    }

    return 0;
}