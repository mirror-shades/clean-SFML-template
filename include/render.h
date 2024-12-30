#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "tile.h"
#include "map.h"
#include "player.h"
#include "monsterManager.h"
#include "environment.h"
#include "battle.h"

class Engine;

enum AnimationState
{
    IDLE,
    ATTACKING,
    EFFECT,
    DEFENDING
};
struct BattleAnimation
{
    AnimationState state;
    int sourceIndex; // Which monster is performing the action
    int targetIndex; // Which monster is receiving the action
    float duration;  // How long the animation should last
    float elapsed;   // How long the animation has been running
};

class Render
{
public:
    int selection;
    std::vector<std::string> options;
    void loadFont();
    void drawPlayer(sf::RenderWindow &window, Player &player);
    void drawScreen(int state, int selection, std::vector<std::string> menuOptions);
    void drawBattle(sf::RenderWindow &window, Player &player, Environment &environment, int &selection, Battle &battle, std::vector<std::string> menuOptions);
    void drawLevelSelect(sf::RenderWindow &window, int &selection, std::vector<std::string> menuOptions);
    void drawAttackMenu(sf::RenderWindow &window, int &selection, int screenWidth, int screenHeight, std::vector<std::string> menuOptions);
    bool isAnimating();
    void updateAnimation(float deltaTime);
    BattleAnimation *getCurrentAnimation();
    void queueAnimation(AnimationState state, int source, int target, float duration);
    void setReferences(sf::RenderWindow &w, MapHandler &m, Player &p,
                       MonsterManager &mm, Environment &env, Battle &b);

private:
    sf::Texture playerMonsterTexture;
    sf::Texture enemyMonsterTexture;
    void drawBackground(sf::RenderWindow &window);
    void drawMap(sf::RenderWindow &window, const MapHandler &map);
    void drawTile(sf::RenderWindow &window, const Tile &tile, int x, int y);
    void drawSymbol(sf::RenderWindow &window, char symbol, int x, int y);
    void drawMenu(sf::RenderWindow &window, int &selection, std::vector<std::string> menuOptions);
    void drawOverlay(sf::RenderWindow &window, Environment &environment, Player &player);
    std::vector<BattleAnimation> animationQueue;
    void drawBattleWithAnimation(sf::RenderWindow &window, const BattleAnimation &anim,
                                 std::vector<sf::Vector2f> &leftPositions,
                                 std::vector<sf::Vector2f> &rightPositions);
    // references
    sf::RenderWindow *window;
    MapHandler *map;
    Player *player;
    MonsterManager *monsterManager;
    Environment *environment;
    Battle *battle;
};
