#include "menu.h"
#include <iostream>

void Menu::setMenuOptions(std::vector<std::string> newOptions)
{
    menuOptions = newOptions;
}

std::vector<std::string> Menu::getMenuOptions(int newState, Player &player)
{
    if (newState == 1) // Main Menu
    {
        menuOptions = {"Fire", "Water", "Earth", "Air"};
    }
    else if (newState == 3) // Level Select
    {
        menuOptions = {"Level 1", "Level 2", "Level 3"};
    }
    else if (newState == 4) // Monster Encountered
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
    return menuOptions;
}

bool Menu::handleMenuSelection(sf::Event event, int &selection)
{
    if (menuOptions.empty())
        return false;

    std::cout << "Selection: " << selection << std::endl;
    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
    {
        selection = (selection - 1 + menuOptions.size()) % menuOptions.size();
        return false;
    }
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
    {
        selection = (selection + 1) % menuOptions.size();
        return false;
    }
    if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)
    {
        return true;
    }
    return false;
}