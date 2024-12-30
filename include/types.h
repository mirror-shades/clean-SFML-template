#pragma once

typedef enum GameState
{
    GAME_OVER,
    GAME_MAIN_MENU,
    GAME_RUNNING,
    GAME_LEVEL_SELECT,
    GAME_MONSTER_ENCOUNTERED
} GameState;

typedef enum Color : unsigned char
{
    RED = 0xE0,     // 111 000 00
    GREEN = 0x1C,   // 000 111 00
    BLUE = 0x03,    // 000 000 11
    YELLOW = 0xFC,  // 111 111 00
    MAGENTA = 0xE3, // 111 000 11
    CYAN = 0x1F,    // 000 111 11
    WHITE = 0xFF,   // 111 111 11
    BLACK = 0x00    // 000 000 00
} Color;

typedef enum AnimationState
{
    IDLE,
    ATTACKING,
    EFFECT,
    DEFENDING
} AnimationState;

typedef enum MoveName
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

} MoveName;

typedef enum MoveType
{
    PHYSICAL,
    SPECIAL,
    STATUS
} MoveType;

typedef enum TargetType
{
    SINGLE_ENEMY, // Standard attack on one enemy
    ALL_ENEMIES,  // Hits all enemies (like an AOE attack)
    SINGLE_ALLY,  // Heal or buff one ally
    ALL_ALLIES,   // Team-wide heal or buff
    SELF,         // Self-buff or heal
    ALL,          // Hits everyone except self
} TargetType;

enum class Faction
{
    PLAYER,
    ENEMY
};

enum ElementType
{
    FIRE,
    WATER,
    EARTH,
    AIR,
    CYBERNETIC,
    ELDRITCH,
    DEMONIC,
    DIVINE,
    ELECTRIC,
    DRAGON,
    PSYCHIC,
    FIGHTING,
    NORMAL,
};