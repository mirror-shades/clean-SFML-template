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
#include "environment.h"
#include "battle.h"
#include "menu.h"

bool needsUpdate = true;

const std::string MAP_DATA[] = {
    "########################",
    "#                      #",
    "#                      #",
    "#                      #",
    "#          gggg        #",
    "#          gggg        #",
    "#          gggg        #",
    "#          gggg        #",
    "#                      #",
    "#                      #",
    "#                      #",
    "#                      #",
    "#                      #",
    "#                      #",
    "#                      #",
    "########################"};

enum GameState
{
    GAME_OVER = 0,
    GAME_MAIN_MENU = 1,
    GAME_RUNNING = 2,
    GAME_LEVEL_SELECT = 3,
    GAME_MONSTER_ENCOUNTERED = 4
};

void setState(GameState &state, int newState)
{
    state = static_cast<GameState>(newState);
    needsUpdate = true;
}

void loadMapFromStrings(MapHandler &map, const std::string mapData[])
{
    Map newMap;
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            char c = mapData[y][x];
            bool walkable = (c == ' ' || c == 'g');
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
    Battle battle;
    GameState state;
    InputManager inputManager;
    MonsterManager monsterManager;
    Environment environment;
    Menu menu;

    // Initialize game state
    int selection = 0;

    // Initialize game state
    setState(state, GAME_MAIN_MENU);
    monsterManager.initializeMoveTypes();
    monsterManager.initializeMonsterTypes();
    inputManager.setReferences(player, monsterManager, map, engine, battle);
    render.setReferences(window, map, player, monsterManager, environment, battle);
    render.loadFont();
    loadMapFromStrings(map, MAP_DATA);

    // Initialize player position
    player.setPosition(5, 5);
    menu.getMenuOptions(state, player);

    sf::Clock battleClock;
    const float BATTLE_TICK_INTERVAL = 0.1f; // 100ms between battle updates

    sf::Clock animationClock;

    while (window.isOpen())
    {
        float deltaTime = animationClock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                std::vector<std::string> menuOptions;
                if (state == GAME_MAIN_MENU)
                {
                    bool menuResult = menu.handleMenuSelection(event, selection);
                    needsUpdate = true; // Always update on menu interaction
                    if (menuResult)     // Only check the result once
                    {
                        menuOptions = menu.getMenuOptions(state, player);
                        std::string picked = menuOptions[selection];
                        std::cout << "Picked: " << picked << std::endl;
                        inputManager.handleMainMenuSelection(picked, player, monsterManager);
                        menu.getMenuOptions(GAME_LEVEL_SELECT, player);
                        menu.setMenuOptions(menuOptions);
                        selection = 0;
                        setState(state, GAME_LEVEL_SELECT);
                    }
                }
                else if (state == GAME_LEVEL_SELECT)
                {
                    bool menuResult = menu.handleMenuSelection(event, selection);
                    needsUpdate = true;
                    if (menuResult)
                    {
                        menuOptions = menu.getMenuOptions(GAME_LEVEL_SELECT, player);
                        std::string picked = menuOptions[selection];
                        setState(state, GAME_RUNNING);
                    }
                }
                else
                {
                    menuOptions = menu.getMenuOptions(GAME_RUNNING, player);
                    bool inputResult = inputManager.walk(event, state, selection, menuOptions);
                    needsUpdate = true;
                    if (inputResult)
                    {
                        if (engine.checkGrass(map, player, environment, monsterManager, battle, state))
                        {
                            setState(state, GAME_MONSTER_ENCOUNTERED);
                        }
                    }
                }
            }
        }

        // Add battle logic update
        if (state == GAME_MONSTER_ENCOUNTERED)
        {
            if (battleClock.getElapsedTime().asSeconds() >= BATTLE_TICK_INTERVAL)
            {
                needsUpdate = true;
                battleClock.restart();
            }
        }

        render.updateAnimation(deltaTime);

        if (needsUpdate || render.getCurrentAnimation())
        {
            std::vector<std::string> menuOptions = menu.getMenuOptions(state, player);
            window.clear();
            render.drawScreen(state, selection, menuOptions);
            if (!render.isAnimating())
                engine.battleTick(player, environment, battle);
            window.display();
            needsUpdate = false;
        }
    }

    return 0;
}