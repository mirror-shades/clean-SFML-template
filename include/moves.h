#pragma once

#include <string>
#include "types.h"

struct Move
{
    MoveName name;
    MoveType type;
    ElementType element;
    int power;
    int accuracy;
    int moveCost;
    std::string moveName;
    TargetType targetType;
};

extern std::vector<Move> moveTypes;

inline void initializeMoveTypes()
{
    moveTypes.clear();
    moveTypes.resize(5);
    moveTypes[1] = {SPARK, SPECIAL, FIRE, 45, 90, 0, "Spark", SINGLE_ENEMY};
    moveTypes[2] = {CLOD, PHYSICAL, EARTH, 50, 85, 0, "Clod", SINGLE_ENEMY};
    moveTypes[3] = {DRIP, PHYSICAL, WATER, 35, 100, 0, "Drip", SINGLE_ENEMY};
    moveTypes[4] = {BREEZE, SPECIAL, AIR, 40, 95, 0, "Breeze", SINGLE_ENEMY};
}
