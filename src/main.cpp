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
extern std::vector<std::string> menuOptions;

Tile level1[24][16] = {
    {
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile('"', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile(' ', Color::BLUE, true),
        Tile('#', Color::BLUE, false),
    },
    {
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
        Tile('#', Color::BLUE, false),
    }};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "");
    Render render;
    Map map;
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

    memcpy(map.currentMap, level1, sizeof(level1));
    bool needsUpdate = true;

    // Initialize player position
    player.setPosition(5, 5);

    // Set initial options based on game state
    if (engine.getState() == GAME_MAIN_MENU)
    {
        menuOptions = {"Fire", "Water", "Earth", "Air"};
    }
    else if (engine.getState() == GAME_MONSTER_ENCOUNTERED)
    {
        menuOptions.clear();
        menuOptions.push_back(player.getActiveMonster(0).moves[0].moveName);
        if (player.getActiveMonster(0).moves.size() > 1)
        {
            menuOptions.push_back(player.getActiveMonster(0).moves[1].moveName);
        }
        else
        {
            menuOptions.push_back("-");
        }
        if (player.getActiveMonster(0).moves.size() > 2)
        {
            menuOptions.push_back(player.getActiveMonster(0).moves[2].moveName);
        }
        else
        {
            menuOptions.push_back("-");
        }
        menuOptions.push_back("Switch");
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
                needsUpdate = inputManager.handleInput(event, player, monsterManager, map, engine, menuOptions, render.selection);
            }
        }

        if (needsUpdate)
        {
            window.clear();
            engine.update(map, player, environment, monsterManager);
            render.drawScreen(window, engine, map, player, monsterManager, environment, menuOptions, render.selection);
            window.display();
            needsUpdate = false;
        }
    }

    return 0;
}