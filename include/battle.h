#pragma once
#include <vector>
#include <string>
#include "player.h"
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
    void addTurn(BattleTurn turn);
    void clearBattleHistory();
    BattleTurn getLastTurn();
    std::vector<BattleTurn> getBattleHistory();
    void executeAIMove(Monster &attacker, std::vector<Monster> &targets);
    float getTypeEffectiveness(ElementType moveType, ElementType targetType);
    void executePlayerMove(Monster &attacker, Monster &target, int moveIndex);
    int calculateMoveDamage(const Monster &attacker, const Monster &target, const Move &move);

private:
    std::vector<BattleTurn> battleHistory;
};
