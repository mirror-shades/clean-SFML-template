#include "input.h"

bool InputManager::handleInput(sf::Event event, Player &player, PlayerManager &playerManager, Map &map)
{
    // Store potential new position
    auto [newX, newY] = playerManager.getPlayerPosition();

    if (event.key.code == sf::Keyboard::W)
        newY--;
    if (event.key.code == sf::Keyboard::S)
        newY++;
    if (event.key.code == sf::Keyboard::A)
        newX--;
    if (event.key.code == sf::Keyboard::D)
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