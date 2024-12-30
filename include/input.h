#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "player.h"
#include "map.h"
#include "engine.h"
#include "monsterManager.h"

class InputManager
{
public:
    bool walk(sf::Event event, int state, int &selection, std::vector<std::string> menuOptions);
    bool handleBattleInput(sf::Event event, int &selection, std::vector<std::string> menuOptions);
    void setReferences(Player &p, MonsterManager &mm, MapHandler &m, Engine &e, Battle &b);
    void handleMainMenuSelection(std::string selection, Player &player, MonsterManager &monsterManager);

private:
    Player *player;
    MonsterManager *monsterManager;
    MapHandler *map;
    Engine *engine;
    Battle *battle;
};