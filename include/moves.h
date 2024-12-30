#pragma once

#include <string>
#include "elements.h"

enum MoveName
{
    // normal
    WHACK,
    SMACK,
    SHALLACK,
    // fire
    SPARK,
    TORCH,
    INFERNO,
    // earth
    CLOD,
    MUDSLIDE,
    TREEFALL,
    // water
    DRIP,
    WAVE,
    FLOOD,
    // air
    BREEZE,
    GALE,
    TORNADO,
    // cybernetic
    FIZZ,
    BUZZ,
    SHORTCIRCUIT,
    // eldritch
    WHISPER,
    VOID,
    MADNESS,
    // demonic
    SCREAM,
    TORMENT,
    PLAGUE,
    // divine
    PRAY,
    BLESS,
    MIRACLE,
    // electric
    ZAP,
    SHOCK,
    HIGHVOLTAGE,
    // dragon
    SLICE,
    CHOMP,
    BREATHE,
    // psychic
    GASLIGHT,
    MINDGAME,
    HALLUCINATE,
    // fighting
    PUNCH,
    KICK,
    GRAPPLE,

};

enum MoveType
{
    PHYSICAL,
    SPECIAL,
    STATUS
};

enum TargetType
{
    SINGLE_ENEMY, // Standard attack on one enemy
    ALL_ENEMIES,  // Hits all enemies (like an AOE attack)
    SINGLE_ALLY,  // Heal or buff one ally
    ALL_ALLIES,   // Team-wide heal or buff
    SELF,         // Self-buff or heal
    ALL,          // Hits everyone except self
};

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
