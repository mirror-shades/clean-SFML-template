#include <iostream>
#include "input.h"
#include "engine.h"

bool InputManager::handleInput(sf::Event event, Player &player, MonsterManager &monsterManager, Map &map, Engine &engine, std::vector<std::string> options, int &selection)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (engine.state == GAME_RUNNING)
        {
            return movePlayer(event, player, map);
        }
        if (engine.state == GAME_MENU)
        {
            if (moveMenu(event, selection, options))
            {
                // menu selected
                handleMenuSelection(options[selection], player, monsterManager);
                engine.state = GAME_RUNNING;
            }
            return true;
        }
    }
    return false;
}

void InputManager::handleMenuSelection(std::string selection, Player &player, MonsterManager &monsterManager)
{
    if (selection == "Fire")
    {
        player.addMonster(1, monsterManager);
    }
    else if (selection == "Water")
    {
        player.addMonster(2, monsterManager);
    }
    else if (selection == "Earth")
    {
        player.addMonster(3, monsterManager);
    }
    else if (selection == "Air")
    {
        player.addMonster(4, monsterManager);
    }
}

bool InputManager::moveMenu(sf::Event event, int &selection, std::vector<std::string> options)
{
    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        selection = updateSelection(options.size(), -1, selection);
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        selection = updateSelection(options.size(), 1, selection);
    if (event.key.code == sf::Keyboard::Enter or event.key.code == sf::Keyboard::Space)
        return true;
    return false;
}

int InputManager::updateSelection(int options, int change, int &selection)
{
    int newSelection = (selection + change) % options;
    if (newSelection < 0)
        newSelection = options - 1;
    return newSelection;
}

bool InputManager::movePlayer(sf::Event event, Player &player, Map &map)
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
        player.setPosition(newX, newY);
        return true;
    }
    else
    {
        return false;
    }
}