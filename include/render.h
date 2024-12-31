#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "tile.h"
#include "map.h"
#include "player.h"
#include "monsterManager.h"
#include "environment.h"
#include "battle.h"

class Engine;

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
    void drawPlayer();
    void drawScreen(int state, int selection, std::vector<std::string> menuOptions);
    void drawBattle(int &selection, std::vector<std::string> menuOptions);
    void drawLevelSelect(int &selection, std::vector<std::string> menuOptions);
    void drawAttackMenu(int &selection, int screenWidth, int screenHeight, std::vector<std::string> menuOptions);
    bool isAnimating();
    void updateAnimation(float deltaTime);
    void queueAttackSequence(AnimationState attackDirection, int sourceIndex, int targetIndex);
    BattleAnimation *getCurrentAnimation();
    std::vector<BattleAnimation> getAnimationQueue();
    void queueAnimation(AnimationState state, int source, int target, float duration);
    void setReferences(sf::RenderWindow &w, MapHandler &m, Player &p,
                       MonsterManager &mm, Environment &env, Battle &b);
    void initializeBattlePositions(int screenWidth, int screenHeight);
    void resetBattlePositions();

private:
    sf::Texture playerMonsterTexture;
    sf::Texture enemyMonsterTexture;
    void drawBackground();
    void drawMap();
    void drawTile(const Tile &tile, int x, int y);
    void drawSymbol(char symbol, int x, int y);
    void drawMenu(int &selection, std::vector<std::string> menuOptions);
    void drawOverlay();
    std::vector<BattleAnimation> animationQueue;
    void drawBattleWithAnimation(const BattleAnimation &anim,
                                 std::vector<sf::Vector2f> &leftPositions,
                                 std::vector<sf::Vector2f> &rightPositions);
    // references
    sf::RenderWindow *window;
    MapHandler *map;
    Player *player;
    MonsterManager *monsterManager;
    Environment *environment;
    Battle *battle;
    std::vector<sf::Vector2f> leftPositions;
    std::vector<sf::Vector2f> rightPositions;
    std::vector<sf::Vector2f> leftOriginalPositions;
    std::vector<sf::Vector2f> rightOriginalPositions;
};
