#include <iostream>
#include <random>
#include "engine.h"
#include "map.h"
#include "player.h"
#include "monster.h"
#include "elements.h"
std::vector<std::string> menuOptions;

void Engine::checkGrass(MapHandler &map, Player &player, Environment &environment, MonsterManager &monsterManager)
{
    // random seed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000000);
    // check to see what tile the player is on
    // if the tile is " they are on grass
    // return a cout statement saying they are on grass
    if (map.getCurrentTile(player.getPosition().first, player.getPosition().second).symbol == 'g' and getState() == GAME_RUNNING)
    {
        // if the player is on grass, they have a 15% chance to encounter a monster
        if ((dis(gen) % 100) < 15)
        {
            environment.addEnemyMonster(monsterManager.createMonster((dis(gen) % 4) + 1));
            environment.addEnemyMonster(monsterManager.createMonster((dis(gen) % 4) + 1));
            environment.addEnemyMonster(monsterManager.createMonster((dis(gen) % 4) + 1));
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

bool Engine::movePlayer(sf::Event event, Player &player, MapHandler &map)
{
    // Store potential new position
    auto [newX, newY] = player.getPosition();

    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        newY--;
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        newY++;
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
        newX--;
    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
        newX++;

    // Only update position if the move is valid
    if (map.isValidMove(newX, newY))
    {
        player.setSteps(player.getSteps() - 1);
        player.setPosition(newX, newY);
        return true;
    }
    else
    {
        return false;
    }
}

void Engine::battleTick(Player &player, Environment &environment)
{
    auto playerMonsters = player.getActiveMonsters();
    auto enemyMonsters = environment.getEnemyMonsters();
    // for each monster in the player and enemy party, increase their turn points based on their speed
    for (Monster &monster : playerMonsters)
    {
        monster.currentTurnPoints += monster.speed / 2;
    }
    // for each monster in the enemy party, increase their turn points based on their speed
    for (Monster &monster : enemyMonsters)
    {
        monster.currentTurnPoints += monster.speed / 2;
    }
    // them increase their move points based on their special attack
    for (Monster &monster : playerMonsters)
    {
        monster.currentMovePoints += monster.specialAttack / 4;
    }
    // for each monster in the enemy party, increase their move points based on their special attack
    for (Monster &monster : enemyMonsters)
    {
        monster.currentMovePoints += monster.specialAttack / 4;
    }

    // if any monster has 100 or more turn points, set their turn points to 0
    for (Monster &monster : playerMonsters)
    {
        if (monster.currentTurnPoints >= 1000)
        {
            monster.currentTurnPoints = 0;
        }
        if (monster.currentMovePoints >= 1000)
        {
            monster.currentMovePoints = 1000;
        }
    }

    // if any monster has 100 or more move points, set their move points to 100
    for (Monster &monster : enemyMonsters)
    {
        if (monster.currentTurnPoints >= 1000)
        {
            monster.currentTurnPoints = 0;
        }
        if (monster.currentMovePoints >= 1000)
        {
            monster.currentMovePoints = 1000;
        }
    }
    player.updateActiveMonsters(playerMonsters);
    environment.updateEnemyMonsters(enemyMonsters);
}
