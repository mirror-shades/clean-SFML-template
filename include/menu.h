#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "player.h"

class Menu
{
public:
    void setMenuOptions(std::vector<std::string> newOptions);
    std::vector<std::string> getMenuOptions(int newState, Player &player);
    bool handleMenuSelection(sf::Event event, int &selection);

private:
    std::vector<std::string> menuOptions;
};
