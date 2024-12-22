#include <SFML/Graphics.hpp>
#include "map.h"
#include "render.h"
#include "tile.h"
#include "colors.h"
#include "engine.h"
#include <iostream>

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

bool isValidMove(const Map &map, int x, int y)
{
    // Check bounds
    if (x < 0 || x >= 24 || y < 0 || y >= 16)
    {
        return false;
    }
    // Check if tile is walkable
    return map.currentMap[x][y].walkable;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    Render render;
    render.loadFont();
    Map map;
    memcpy(map.currentMap, level1, sizeof(level1));
    Player player = {5, 5};
    Engine engine;
    // test map
    bool needsUpdate = true; // Initial draw flag
    engine.state = GAME_RUNNING;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                // Store potential new position
                int newX = player.x;
                int newY = player.y;

                if (event.key.code == sf::Keyboard::W)
                    newY--;
                if (event.key.code == sf::Keyboard::S)
                    newY++;
                if (event.key.code == sf::Keyboard::A)
                    newX--;
                if (event.key.code == sf::Keyboard::D)
                    newX++;

                // Only update position if the move is valid
                if (isValidMove(map, newX, newY))
                {
                    player.x = newX;
                    player.y = newY;
                    needsUpdate = true;
                }
            }
        }

        // Only draw if update is needed
        if (needsUpdate)
        {
            window.clear();
            engine.update(map, player);
            render.drawScreen(window, engine, map, player);
            window.display();
            needsUpdate = false; // Reset the flag after drawing
        }
    }

    return 0;
}