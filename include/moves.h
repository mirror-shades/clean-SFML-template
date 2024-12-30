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

struct Move
{
    MoveName name;
    MoveType type;
    ElementType element;
    int power;
    int accuracy;
    std::string moveName;
};

extern std::vector<Move> moveTypes;

inline void initializeMoveTypes()
{
    moveTypes.clear();
    moveTypes.resize(5);
    moveTypes[1] = {SPARK, SPECIAL, FIRE, 45, 90, "Spark"};
    moveTypes[2] = {CLOD, PHYSICAL, EARTH, 50, 85, "Clod"};
    moveTypes[3] = {DRIP, PHYSICAL, WATER, 35, 100, "Drip"};
    moveTypes[4] = {BREEZE, SPECIAL, AIR, 40, 95, "Breeze"};
}
