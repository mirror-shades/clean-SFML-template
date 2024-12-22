#pragma once

#include <map>
#include <string>

enum ElementType
{
    FIRE,
    WATER,
    EARTH,
    AIR
};

// Base monster type definition
struct MonsterType
{
    int id;
    ElementType element;
    std::string name;
    float baseHealth;
    float baseAttack;
    float baseSpecialAttack;
    float baseDefense;
    float baseSpecialDefense;
    float baseMagic;
    float baseAccuracy;
    float baseEvasion;
    float baseSpeed;
};

extern std::map<int, MonsterType> monsterTypes;

// Actual monster instance
struct Monster
{
    int id;
    ElementType element;
    std::string name;
    int health;
    int attack;
    int specialAttack;
    int defense;
    int specialDefense;
    int magic;
    int accuracy;
    int evasion;
    int speed;
    int x;
    int y;
};

// Base monster types with stats divided by 10
inline void initializeMonsterTypes()
{
    MonsterType phoenix = {
        1,         // id
        FIRE,      // element
        "Phoenix", // name
        10.0f,     // baseHealth    (100/10)
        7.5f,      // baseAttack     (75/10)
        9.0f,      // baseSpecialAttack
        6.0f,      // baseDefense
        7.0f,      // baseSpecialDefense
        8.5f,      // baseMagic
        8.0f,      // baseAccuracy
        7.5f,      // baseEvasion
        9.0f       // baseSpeed
    };

    MonsterType leviathan = {
        2,           // id
        WATER,       // element
        "Leviathan", // name
        12.0f,       // baseHealth
        7.0f,        // baseAttack
        8.5f,        // baseSpecialAttack
        8.0f,        // baseDefense
        8.5f,        // baseSpecialDefense
        7.5f,        // baseMagic
        8.5f,        // baseAccuracy
        7.0f,        // baseEvasion
        6.5f         // baseSpeed
    };

    MonsterType golem = {
        3,       // id
        EARTH,   // element
        "Golem", // name
        15.0f,   // baseHealth
        9.5f,    // baseAttack
        6.0f,    // baseSpecialAttack
        10.0f,   // baseDefense
        9.0f,    // baseSpecialDefense
        4.5f,    // baseMagic
        7.0f,    // baseAccuracy
        4.0f,    // baseEvasion
        3.0f     // baseSpeed
    };

    MonsterType sylph = {
        4,       // id
        AIR,     // element
        "Sylph", // name
        8.0f,    // baseHealth
        6.0f,    // baseAttack
        8.5f,    // baseSpecialAttack
        5.0f,    // baseDefense
        6.5f,    // baseSpecialDefense
        9.5f,    // baseMagic
        9.5f,    // baseAccuracy
        10.0f,   // baseEvasion
        10.0f    // baseSpeed
    };

    monsterTypes[1] = phoenix;
    monsterTypes[2] = leviathan;
    monsterTypes[3] = golem;
    monsterTypes[4] = sylph;
}

class MonsterManager
{
public:
    Monster createMonster(const MonsterType &baseType);
};
