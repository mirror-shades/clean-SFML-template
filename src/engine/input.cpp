#include <iostream>
#include <utility>
#include "input.h"
#include "engine.h"

bool InputManager::walk(sf::Event event, int state, int &selection, std::vector<std::string> menuOptions)
{
    std::cout << "Event: " << event.type
              << " Key: " << event.key.code
              << " State: " << state
              << " Selection: " << selection
              << " MenuSize: " << menuOptions.size() << std::endl;
    bool playerMoved = false;
    playerMoved = engine->movePlayer(event, *player, *map);
    return playerMoved;
}

void InputManager::handleMainMenuSelection(std::string selection, Player &player, MonsterManager &monsterManager)
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
    // testing
    player.addMonster(1, monsterManager);
    player.addMonster(2, monsterManager);
    std::cout << "Selection: " << selection << std::endl;
}

bool InputManager::handleBattleInput(sf::Event event, int &selection, std::vector<std::string> menuOptions)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            selection = 0;
        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
            selection = 1;
        if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            selection = 2;
        if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            selection = 3;
        if (event.key.code == sf::Keyboard::Enter or event.key.code == sf::Keyboard::Space)
        {
            if (menuOptions[selection] == "Switch")
            {
                battle->deinit(*player);
                std::vector<Monster> playerMonsters = player->getActiveMonsters();
            }
            else if (menuOptions[selection] == "-")
            {
            }
            else
            {
                std::cout << menuOptions[selection] << std::endl;
            }
        }
        return true;
    }
    return false;
}

void InputManager::setReferences(Player &p, MonsterManager &mm, MapHandler &m, Engine &e, Battle &b)
{
    player = &p;
    monsterManager = &mm;
    map = &m;
    engine = &e;
    battle = &b;
}
