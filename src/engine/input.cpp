#include "input.h"
#include "engine.h"
#include "menu.h"

bool InputManager::handleInput(sf::Event event, Player &player, PlayerManager &playerManager, Map &map, Engine &engine, Menu &menu, std::vector<std::string> options)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (engine.state == GAME_RUNNING)
        {
            return movePlayer(event, player, playerManager, map);
        }
        if (engine.state == GAME_MENU)
        {
            if (moveMenu(event, menu, options))
            {
                // menu selected
                // handleMenuSelection(options[menu.selection]);
                engine.state = GAME_RUNNING;
            }
            return true;
        }
    }
    return false;
}

bool InputManager::moveMenu(sf::Event event, Menu &menu, std::vector<std::string> options)
{
    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        menu.selection = updateSelection(options.size(), -1, menu);
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        menu.selection = updateSelection(options.size(), 1, menu);
    if (event.key.code == sf::Keyboard::Enter or event.key.code == sf::Keyboard::Space)
        return true;
    return false;
}

int InputManager::updateSelection(int options, int change, Menu &menu)
{
    int newSelection = (menu.selection + change) % options;
    if (newSelection < 0)
        newSelection = options - 1;
    return newSelection;
}

bool InputManager::movePlayer(sf::Event event, Player &player, PlayerManager &playerManager, Map &map)
{
    // Store potential new position
    auto [newX, newY] = playerManager.getPlayerPosition();

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
        playerManager.setPlayerPosition(newX, newY);
        return true;
    }
    else
    {
        return false;
    }
}