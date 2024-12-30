#include "engine.h"
#include "battle.h"
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

std::vector<std::string> menuOptions;

void Engine::checkGrass(MapHandler &map, Player &player, Environment &environment, MonsterManager &monsterManager)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000000);

    if (map.getCurrentTile(player.getPosition().first, player.getPosition().second).symbol == 'g' and getState() == GAME_RUNNING)
    {
        if ((dis(gen) % 100) < 15) // 15% chance to encounter a monster
        {
            environment.addEnemyMonster(monsterManager.createMonster((dis(gen) % 4) + 1, Faction::ENEMY));
            environment.addEnemyMonster(monsterManager.createMonster((dis(gen) % 4) + 1, Faction::ENEMY));
            environment.addEnemyMonster(monsterManager.createMonster((dis(gen) % 4) + 1, Faction::ENEMY));
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

void Engine::battleTick(Player &player, Environment &environment, Battle &battle)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    auto &playerMonsters = player.getActiveMonsters();
    auto &enemyMonsters = environment.getEnemyMonsters();
    std::vector<Monster *> allMonsters;
    std::vector<Monster *> readyToAct;

    // Add pointers to all monsters
    for (auto &monster : playerMonsters)
    {
        allMonsters.push_back(&monster);
    }
    for (auto &monster : enemyMonsters)
    {
        allMonsters.push_back(&monster);
    }

    // Accumulate turn points and find ready monsters
    for (auto *monster : allMonsters)
    {
        if (monster->currentHealth <= 0)
            continue; // Skip dead monsters

        monster->currentTurnPoints += monster->speed / 4;
        monster->currentMovePoints += monster->specialAttack / 8;

        // Only add to ready list if they have 1000+ points
        if (monster->currentTurnPoints >= 1000)
        {
            readyToAct.push_back(monster);
            monster->currentTurnPoints -= 1000; // Deduct points immediately
        }
        if (monster->currentMovePoints >= 1000)
        {
            monster->currentMovePoints = 1000;
        }
    }

    // Process ready monsters
    for (auto *monster : readyToAct)
    {
        if (!monster->currentHealth > 0)
            continue; // Double check they're still alive

        bool isPlayerMonster = std::find_if(playerMonsters.begin(), playerMonsters.end(),
                                            [monster](Monster &m)
                                            { return &m == monster; }) != playerMonsters.end();

        if (isPlayerMonster)
        {
            battle.executeAIMove(*monster, enemyMonsters);
        }
        else
        {
            battle.executeAIMove(*monster, playerMonsters);
        }
    }

    checkIfMonsterDies(playerMonsters, enemyMonsters, environment, player);
}

void Engine::checkIfMonsterDies(std::vector<Monster> &playerMonsters, std::vector<Monster> &enemyMonsters, Environment &environment, Player &player)
{
    // Only remove dead enemy monsters
    for (auto &monster : enemyMonsters)
    {
        if (monster.currentHealth <= 0)
        {
            enemyMonsters.erase(std::remove(enemyMonsters.begin(), enemyMonsters.end(), monster), enemyMonsters.end());
        }
    }

    if (enemyMonsters.empty())
    {
        environment.clearEnemyMonsters();
        restorePlayerMonsters(playerMonsters, player);
        setState(GAME_RUNNING, player);
    }
    bool allyAlive = false;
    for (auto &monster : playerMonsters)
    {
        if (monster.currentHealth > 0)
        {
            allyAlive = true;
        }
    }
    if (!allyAlive)
    {
        // implement game over here
        environment.clearEnemyMonsters();
        restorePlayerMonsters(playerMonsters, player);
        setState(GAME_RUNNING, player);
    }
}

void Engine::restorePlayerMonsters(std::vector<Monster> &playerMonsters, Player &player)
{
    for (auto &monster : playerMonsters)
    {
        monster.currentHealth = monster.health;
        monster.currentTurnPoints = 0;
        monster.currentMovePoints = 0;
    }
    player.updateActiveMonsters(playerMonsters);
}

void Engine::determineTurnOrder(std::vector<Monster> &monsters)
{
    // sort the monsters by speed
    std::sort(monsters.begin(), monsters.end(), [](Monster &a, Monster &b)
              { return a.speed > b.speed; });
}
