#include <iostream>
#include <random>
#include "engine.h"
#include "map.h"
#include "player.h"

void Engine::update(Map &map, Player &player)
{
    // random seed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    // check to see what tile the player is on
    // if the tile is " they are on grass
    // return a cout statement saying they are on grass
    if (map.getCurrentTile(player).symbol == '"')
    {
        // if the player is on grass, they have a 15% chance to encounter a monster
        if (dis(gen) < 15)
        {
            std::cout << "Monster encountered!" << std::endl;
        }
    }
}