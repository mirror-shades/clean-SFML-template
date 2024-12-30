#pragma once
#include <vector>
#include <string>
#include "player.h"
#include "monster.h"
#include "environment.h"

struct BattleTurn
{
    int attackerId;
    std::string moveName;
    std::vector<int> targetIds;
    std::string action;
    std::string result;
};

class Battle
{
public:
    void executePlayerMove(Monster &attacker, Monster &target, int moveIndex);
    void executeAIMove(Monster &attacker, std::vector<Monster> &targets);
    void deinit(Player &player);

private:
    std::vector<BattleTurn> battleHistory;

    void addTurn(BattleTurn turn);
    void clearBattleHistory();
    BattleTurn getLastTurn();
    std::vector<BattleTurn> getBattleHistory();
    float getTypeEffectiveness(ElementType moveType, ElementType targetType);
    int calculateMoveDamage(const Monster &attacker, const Monster &target, const Move &move);
    void restoreMonsters(Player &player);
};
