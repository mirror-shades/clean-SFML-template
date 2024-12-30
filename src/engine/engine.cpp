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
    static std::random_device rd;
    static std::mt19937 gen(rd());

    auto playerMonsters = player.getActiveMonsters();
    auto enemyMonsters = environment.getEnemyMonsters();
    std::vector<Monster *> allMonsters;
    std::vector<Monster *> readyToAct;

    // Combine all monsters into one list with pointers
    for (auto &monster : playerMonsters)
    {
        allMonsters.push_back(&monster);
    }
    for (auto &monster : enemyMonsters)
    {
        allMonsters.push_back(&monster);
    }

    // Accumulate turn points for all monsters
    for (auto *monster : allMonsters)
    {
        monster->currentTurnPoints += monster->speed / 2;
        monster->currentMovePoints += monster->specialAttack / 4;
        if (monster->currentTurnPoints >= 1000)
        {
            readyToAct.push_back(monster);
        }
        if (monster->currentMovePoints >= 1000)
        {
            monster->currentMovePoints = 1000;
        }
    }

    // Sort and process ready monsters
    if (!readyToAct.empty())
    {
        std::sort(readyToAct.begin(), readyToAct.end(),
                  [](Monster *a, Monster *b)
                  { return a->speed > b->speed; });

        for (auto *monster : readyToAct)
        {
            monster->currentTurnPoints -= 1000;

            bool isPlayerMonster = std::find_if(playerMonsters.begin(), playerMonsters.end(),
                                                [monster](const Monster &m)
                                                { return &m == monster; }) != playerMonsters.end();

            if (isPlayerMonster)
            {
                // Player monsters attack enemy monsters
                if (!enemyMonsters.empty())
                {
                    executeAIMove(*monster, enemyMonsters);
                }
            }
            else
            {
                // Enemy monsters attack player monsters
                if (!playerMonsters.empty())
                {
                    executeAIMove(*monster, playerMonsters);
                }
            }
            checkIfMonsterDies(playerMonsters, enemyMonsters);
        }
    }

    // Update the collections
    player.updateActiveMonsters(playerMonsters);
    environment.updateEnemyMonsters(enemyMonsters);
}

void Engine::checkIfMonsterDies(std::vector<Monster> &playerMonsters, std::vector<Monster> &enemyMonsters)
{
    for (auto &monster : playerMonsters)
    {
        if (monster.currentHealth <= 0)
        {
            playerMonsters.erase(std::remove(playerMonsters.begin(), playerMonsters.end(), monster), playerMonsters.end());
        }
    }
    for (auto &monster : enemyMonsters)
    {
        if (monster.currentHealth <= 0)
        {
            enemyMonsters.erase(std::remove(enemyMonsters.begin(), enemyMonsters.end(), monster), enemyMonsters.end());
        }
    }
}

void Engine::executeAIMove(Monster &attacker, std::vector<Monster> &targets)
{
    if (!targets.empty())
    {
        Monster &target = targets[0];
        // Calculate and apply damage
        int damage = std::max(1, attacker.attack - target.defense);
        target.currentHealth = std::max(0, target.currentHealth - damage);

        // Debug output to verify damage is being calculated
        std::cout << "AI Attack: " << attacker.name << " deals " << damage
                  << " damage to " << target.name
                  << " (HP: " << target.currentHealth << ")" << std::endl;
    }
}

// Add this function to handle player's move selection
void Engine::executePlayerMove(Monster &attacker, Monster &target, int moveIndex)
{
    // Get the selected move
    if (moveIndex >= 0 && moveIndex < attacker.moves.size())
    {
        Move &selectedMove = attacker.moves[moveIndex];

        // Calculate damage based on move power, attacker's stats, and target's defense
        int damage = calculateMoveDamage(attacker, target, selectedMove);
        target.currentHealth = std::max(0, target.currentHealth - damage);

        // Reset the monster's action flag
        attacker.canAct = false;
    }
}

int Engine::calculateMoveDamage(const Monster &attacker, const Monster &target, const Move &move)
{
    // Basic damage formula
    float baseDamage = move.power * (float)attacker.attack / target.defense;

    // Add type effectiveness (you'll need to implement this)
    float typeMultiplier = 1; // getTypeEffectiveness(move.type, target.type);

    // Add random variation (0.85 to 1.15)
    float random = 0.85f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.3f)));

    return std::max(1, static_cast<int>(baseDamage * typeMultiplier * random));
}

void Engine::determineTurnOrder(std::vector<Monster> &monsters)
{
    // sort the monsters by speed
    std::sort(monsters.begin(), monsters.end(), [](Monster &a, Monster &b)
              { return a.speed > b.speed; });
}
