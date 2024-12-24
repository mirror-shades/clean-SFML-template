#include <iostream>
#include <random>
#include "engine.h"
#include "map.h"
#include "player.h"

std::vector<std::string> menuOptions;

void Engine::update(MapHandler &map, Player &player, Environment &environment, MonsterManager &monsterManager)
{
    // random seed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000000);
    // check to see what tile the player is on
    // if the tile is " they are on grass
    // return a cout statement saying they are on grass
    if (map.getCurrentTile(player.getPosition().first, player.getPosition().second).symbol == '"')
    {
        // if the player is on grass, they have a 15% chance to encounter a monster
        if ((dis(gen) % 100) < 15)
        {
            environment.enemyMonsters.push_back(monsterManager.createMonster((dis(gen) % 4) + 1));
            setState(GAME_MONSTER_ENCOUNTERED, player);
        }
    }
}

gameState Engine::getState()
{
    return state;
}

void Engine::setState(gameState newState, Player &player)
{
    if (newState == GAME_MAIN_MENU)
    {
        menuOptions = {"Fire", "Water", "Earth", "Air"};
    }
    else if (newState == GAME_MONSTER_ENCOUNTERED)
    {
        std::vector<std::string> moves;
        moves.push_back(player.getActiveMonster(0).moves[0].moveName);
        if (player.getActiveMonster(0).moves.size() > 1)
        {
            moves.push_back(player.getActiveMonster(0).moves[1].moveName);
        }
        else
        {
            moves.push_back("-");
        }
        if (player.getActiveMonster(0).moves.size() > 2)
        {
            moves.push_back(player.getActiveMonster(0).moves[2].moveName);
        }
        else
        {
            moves.push_back("-");
        }
        moves.push_back("Switch");
        menuOptions = moves;
    }
    state = newState;
}