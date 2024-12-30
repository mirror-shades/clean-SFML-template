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

void Engine::checkGrass(MapHandler &map, Player &player, Environment &environment, MonsterManager &monsterManager, Battle &battle)
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
        moves.push_back(player.getActiveMonster(0).currentStats.moves[0].moveName);
        if (player.getActiveMonster(0).currentStats.moves.size() > 1)
        {
            moves.push_back(player.getActiveMonster(0).currentStats.moves[1].moveName);
        }
        else
        {
            moves.push_back("-");
        }
        if (player.getActiveMonster(0).currentStats.moves.size() > 2)
        {
            moves.push_back(player.getActiveMonster(0).currentStats.moves[2].moveName);
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

    std::vector<Monster *> allMonsters;
    std::vector<Monster *> readyToAct;

    for (auto &monster : player.getActiveMonsters())
    {
        allMonsters.push_back(&monster);
    }
    for (auto &monster : environment.getEnemyMonsters())
    {
        allMonsters.push_back(&monster);
    }

    // Constants for battle timing
    const float BASE_TURN_THRESHOLD = 100.0f;      // Points needed for a turn
    const float MOVE_THRESHOLD_MULTIPLIER = 10.0f; // Base multiplier for move points

    // Accumulate turn points and find ready monsters
    for (auto *monster : allMonsters)
    {
        if (monster->currentStats.health <= 0)
            continue; // Skip dead monsters

        // Scale speed to a reasonable rate (e.g., fastest monsters take ~2-3 seconds for a turn)
        monster->turnPoints += monster->currentStats.speed * 0.1f;
        monster->movePoints += monster->currentStats.specialAttack * 0.2f;

        // Only add to ready list if they have enough points
        if (monster->turnPoints >= BASE_TURN_THRESHOLD)
        {
            readyToAct.push_back(monster);
            monster->turnPoints = 0; // Reset points
        }

        // Cap move points at threshold
        float moveThreshold = monster->currentStats.specialAttack * MOVE_THRESHOLD_MULTIPLIER;
        if (monster->movePoints >= moveThreshold)
        {
            monster->movePoints = moveThreshold;
        }
    }

    // Process ready monsters
    for (auto *monster : readyToAct)
    {
        if (monster->currentStats.health <= 0)
            continue; // Double check they're still alive

        bool isPlayerMonster = std::find_if(player.getActiveMonsters().begin(), player.getActiveMonsters().end(),
                                            [monster](Monster &m)
                                            { return &m == monster; }) != player.getActiveMonsters().end();

        if (isPlayerMonster)
        {
            battle.executeAIMove(*monster, environment.getEnemyMonsters());
        }
        else
        {
            battle.executeAIMove(*monster, player.getActiveMonsters());
        }
    }

    checkIfMonsterDies(player.getActiveMonsters(), environment.getEnemyMonsters(), environment, player, battle);
}

void Engine::checkIfMonsterDies(std::vector<Monster> &playerBattleMonsters, std::vector<Monster> &enemyBattleMonsters, Environment &environment, Player &player, Battle &battle)
{
    bool enemyAlive = false;
    for (auto &monster : enemyBattleMonsters)
    {
        if (monster.currentStats.health > 0)
        {
            enemyAlive = true;
        }
    }
    if (!enemyAlive)
    {
        // implement win condition here
        environment.clearEnemyMonsters();
        setState(GAME_RUNNING, player);
    }
    bool allyAlive = false;
    for (auto &monster : playerBattleMonsters)
    {
        if (monster.currentStats.health > 0)
        {
            allyAlive = true;
        }
    }
    if (!allyAlive)
    {
        // implement game over here
        environment.clearEnemyMonsters();
        setState(GAME_RUNNING, player);
    }
}

void Engine::determineTurnOrder(std::vector<Monster> &monsters)
{
    // sort the monsters by speed
    std::sort(monsters.begin(), monsters.end(), [](Monster &a, Monster &b)
              {
                  return a.currentStats.speed > b.currentStats.speed; // Access the base monster through the BattleMonster wrapper
              });
}
