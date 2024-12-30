#include <iostream>
#include <utility>
#include "input.h"
#include "engine.h"

std::pair<bool, bool> InputManager::handleInput(sf::Event event, Player &player, MonsterManager &monsterManager, MapHandler &map, Engine &engine, int &selection)
{
    bool playerMoved = false;
    if (event.type == sf::Event::KeyPressed)
    {
        if (engine.getState() == GAME_RUNNING)
        {
            playerMoved = engine.movePlayer(event, player, map);
            return {true, playerMoved};
        }
        if (engine.getState() == GAME_MAIN_MENU)
        {
            if (moveMenu(event, selection, engine.menuOptions))
            {
                // menu selected
                handleMenuSelection(engine.menuOptions[selection], player, monsterManager);
                engine.setState(GAME_LEVEL_SELECT, player);
                selection = 0;
            }
            return {true, playerMoved};
        }
        if (engine.getState() == GAME_MONSTER_ENCOUNTERED)
        {
            return {handleBattleInput(event, selection, player, engine), playerMoved};
        }
        if (engine.getState() == GAME_LEVEL_SELECT)
        {
            return {handleLevelSelectInput(event, selection, engine, player), playerMoved};
        }
    }
    return {false, playerMoved};
}

bool InputManager::handleLevelSelectInput(sf::Event event, int &selection, Engine &engine, Player &player)
{
    std::cout << "Current selection: " << selection << std::endl;

    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
    {
        selection = updateSelection(3, -1, selection);
        std::cout << "Up pressed, new selection: " << selection << std::endl;
    }
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
    {
        selection = updateSelection(3, 1, selection);
        std::cout << "Down pressed, new selection: " << selection << std::endl;
    }
    // this function will also take level options then construct an environment with the selected element
    // for now just switch to the default level
    if (event.key.code == sf::Keyboard::Enter or event.key.code == sf::Keyboard::Space)
    {
        engine.setState(GAME_RUNNING, player);
        return true;
    }
    return true;
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
    // testing
    player.addMonster(1, monsterManager);
    player.addMonster(2, monsterManager);
}

bool InputManager::handleBattleInput(sf::Event event, int &selection, Player &player, Engine &engine)
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
            if (engine.menuOptions[selection] == "Switch")
            {
                engine.setState(GAME_RUNNING, player);
                std::vector<Monster> playerMonsters = player.getActiveMonsters();
                engine.restorePlayerMonsters(playerMonsters, player);
            }
            else if (engine.menuOptions[selection] == "-")
            {
            }
            else
            {
                std::cout << engine.menuOptions[selection] << std::endl;
            }
        }
        return true;
    }
    return false;
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
