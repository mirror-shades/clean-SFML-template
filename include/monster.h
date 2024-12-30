#pragma once

#include <map>
#include <string>
#include <vector>
#include "elements.h"
#include "moves.h"

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
    float baseAccuracy;
    float baseEvasion;
    float baseSpeed;
    int initialMove;
};

extern std::vector<MonsterType> monsterTypes;

enum class Faction
{
    PLAYER,
    ENEMY
};

struct BaseMonster
{
    int id;
    int uid;
    ElementType element;
    std::string name;
    int health;
    int currentHealth;
    int attack;
    int specialAttack;
    int defense;
    int specialDefense;
    int accuracy;
    int evasion;
    int speed;
    std::vector<Move> moves;
    bool canAct;
    Faction faction;
};

struct Monster
{
    BaseMonster currentStats;
    BaseMonster baseStats;
    int turnPoints;
    int movePoints;

    Monster(const BaseMonster &base)
        : currentStats(base), baseStats(base), turnPoints(0), movePoints(0) {}

    Monster(const Monster &other)
        : currentStats(other.currentStats), baseStats(other.baseStats),
          turnPoints(other.turnPoints), movePoints(other.movePoints) {}

    Monster &operator=(const Monster &other) = default;

    bool operator==(const Monster &other) const
    {
        return baseStats.uid == other.baseStats.uid;
    }
};

// Base monster types with stats divided by 10
inline void initializeMonsterTypes()
{
    monsterTypes.clear();
    monsterTypes.resize(5); // Resize to accommodate indices 0-4

    // =========================
    // FIRE
    // =========================
    MonsterType phoenix = {
        1,         // id
        FIRE,      // element
        "Phoenix", // name
        8.0f,      // baseHealth
        7.5f,      // baseAttack
        9.0f,      // baseSpecialAttack
        6.0f,      // baseDefense
        7.0f,      // baseSpecialDefense
        8.0f,      // baseAccuracy
        7.5f,      // baseEvasion
        9.0f,      // baseSpeed
        1};

    MonsterType salamander = {
        5,
        FIRE,
        "Salamander",
        9.0f, // baseHealth
        8.5f, // baseAttack
        8.0f, // baseSpecialAttack
        6.5f, // baseDefense
        6.0f, // baseSpecialDefense
        8.0f, // baseAccuracy
        7.0f, // baseEvasion
        8.5f, // baseSpeed
        1};

    MonsterType ifrit = {
        6,
        FIRE,
        "Ifrit",
        11.0f, // baseHealth
        9.0f,  // baseAttack
        7.5f,  // baseSpecialAttack
        7.0f,  // baseDefense
        6.5f,  // baseSpecialDefense
        8.0f,  // baseAccuracy
        7.0f,  // baseEvasion
        8.0f,  // baseSpeed
        1};

    MonsterType pyreclaw = {
        7,
        FIRE,
        "Pyreclaw",
        10.0f, // baseHealth
        8.0f,  // baseAttack
        8.0f,  // baseSpecialAttack
        5.5f,  // baseDefense
        6.5f,  // baseSpecialDefense
        7.5f,  // baseAccuracy
        8.0f,  // baseEvasion
        8.5f,  // baseSpeed
        1};

    // =========================
    // WATER
    // =========================
    MonsterType leviathan = {
        2,           // id
        WATER,       // element
        "Leviathan", // name
        12.0f,       // baseHealth
        7.0f,        // baseAttack
        8.5f,        // baseSpecialAttack
        8.0f,        // baseDefense
        8.5f,        // baseSpecialDefense
        8.5f,        // baseAccuracy
        7.0f,        // baseEvasion
        6.5f,        // baseSpeed
        3};

    MonsterType kraken = {
        8,
        WATER,
        "Kraken",
        13.0f, // baseHealth
        6.5f,  // baseAttack
        8.0f,  // baseSpecialAttack
        7.5f,  // baseDefense
        8.0f,  // baseSpecialDefense
        7.5f,  // baseAccuracy
        6.5f,  // baseEvasion
        5.5f,  // baseSpeed
        3};

    MonsterType tidalon = {
        9,
        WATER,
        "Tidalon",
        11.0f, // baseHealth
        6.0f,  // baseAttack
        9.0f,  // baseSpecialAttack
        7.5f,  // baseDefense
        9.0f,  // baseSpecialDefense
        8.0f,  // baseAccuracy
        6.5f,  // baseEvasion
        6.0f,  // baseSpeed
        3};

    MonsterType nautilus = {
        10,
        WATER,
        "Nautilus",
        10.0f, // baseHealth
        5.5f,  // baseAttack
        8.0f,  // baseSpecialAttack
        7.0f,  // baseDefense
        7.5f,  // baseSpecialDefense
        7.5f,  // baseAccuracy
        7.0f,  // baseEvasion
        6.0f,  // baseSpeed
        3};

    // =========================
    // EARTH
    // =========================
    MonsterType golem = {
        3,       // id
        EARTH,   // element
        "Golem", // name
        15.0f,   // baseHealth
        9.5f,    // baseAttack
        6.0f,    // baseSpecialAttack
        10.0f,   // baseDefense
        9.0f,    // baseSpecialDefense
        7.0f,    // baseAccuracy
        4.0f,    // baseEvasion
        3.0f,    // baseSpeed
        2};

    MonsterType terrafin = {
        11,
        EARTH,
        "Terrafin",
        14.0f, // baseHealth
        8.5f,  // baseAttack
        5.5f,  // baseSpecialAttack
        9.0f,  // baseDefense
        8.5f,  // baseSpecialDefense
        6.5f,  // baseAccuracy
        4.5f,  // baseEvasion
        3.0f,  // baseSpeed
        2};

    MonsterType quakebeast = {
        12,
        EARTH,
        "Quakebeast",
        16.0f, // baseHealth
        9.0f,  // baseAttack
        5.0f,  // baseSpecialAttack
        10.5f, // baseDefense
        9.5f,  // baseSpecialDefense
        6.0f,  // baseAccuracy
        4.0f,  // baseEvasion
        2.5f,  // baseSpeed
        2};

    MonsterType duramole = {
        13,
        EARTH,
        "Duramole",
        13.5f, // baseHealth
        8.0f,  // baseAttack
        6.0f,  // baseSpecialAttack
        9.0f,  // baseDefense
        8.0f,  // baseSpecialDefense
        6.5f,  // baseAccuracy
        5.0f,  // baseEvasion
        3.5f,  // baseSpeed
        2};

    // =========================
    // AIR
    // =========================
    MonsterType sylph = {
        4,       // id
        AIR,     // element
        "Sylph", // name
        8.0f,    // baseHealth
        6.0f,    // baseAttack
        8.5f,    // baseSpecialAttack
        5.0f,    // baseDefense
        6.5f,    // baseSpecialDefense
        9.5f,    // baseAccuracy
        10.0f,   // baseEvasion
        10.0f,   // baseSpeed
        4};

    MonsterType zephyrwing = {
        14,
        AIR,
        "Zephyrwing",
        7.5f, // baseHealth
        5.5f, // baseAttack
        8.0f, // baseSpecialAttack
        4.5f, // baseDefense
        6.0f, // baseSpecialDefense
        9.5f, // baseAccuracy
        9.0f, // baseEvasion
        9.5f, // baseSpeed
        4};

    MonsterType stratus = {
        15,
        AIR,
        "Stratus",
        9.0f, // baseHealth
        6.0f, // baseAttack
        7.5f, // baseSpecialAttack
        5.0f, // baseDefense
        5.5f, // baseSpecialDefense
        9.0f, // baseAccuracy
        9.0f, // baseEvasion
        9.0f, // baseSpeed
        4};

    MonsterType cloudweaver = {
        16,
        AIR,
        "Cloudweaver",
        7.0f,  // baseHealth
        5.0f,  // baseAttack
        9.5f,  // baseSpecialAttack
        4.0f,  // baseDefense
        6.0f,  // baseSpecialDefense
        9.5f,  // baseAccuracy
        10.5f, // baseEvasion
        10.5f, // baseSpeed
        4};

    // =========================
    // CYBERNETIC
    // =========================
    MonsterType mechadillo = {
        17,
        CYBERNETIC,
        "Mechadillo",
        10.0f, // baseHealth
        6.0f,  // baseAttack
        7.5f,  // baseSpecialAttack
        9.0f,  // baseDefense
        8.5f,  // baseSpecialDefense
        8.0f,  // baseAccuracy
        5.5f,  // baseEvasion
        5.0f,  // baseSpeed
        17};

    MonsterType chronitron = {
        18,
        CYBERNETIC,
        "Chronitron",
        8.0f, // baseHealth
        5.5f, // baseAttack
        9.0f, // baseSpecialAttack
        6.0f, // baseDefense
        6.5f, // baseSpecialDefense
        9.5f, // baseAccuracy
        6.0f, // baseEvasion
        7.0f, // baseSpeed
        18};

    MonsterType circuitros = {
        19,
        CYBERNETIC,
        "Circuitros",
        9.0f, // baseHealth
        5.0f, // baseAttack
        8.5f, // baseSpecialAttack
        5.5f, // baseDefense
        6.5f, // baseSpecialDefense
        8.5f, // baseAccuracy
        7.0f, // baseEvasion
        8.0f, // baseSpeed
        19};

    MonsterType tekknight = {
        20,
        CYBERNETIC,
        "Tekknight",
        12.0f, // baseHealth
        7.5f,  // baseAttack
        7.0f,  // baseSpecialAttack
        9.5f,  // baseDefense
        8.0f,  // baseSpecialDefense
        7.5f,  // baseAccuracy
        5.5f,  // baseEvasion
        6.0f,  // baseSpeed
        20};

    // =========================
    // ELDRITCH
    // =========================
    MonsterType cultling = {
        21,
        ELDRITCH,
        "Cultling",
        9.0f, // baseHealth
        5.5f, // baseAttack
        9.0f, // baseSpecialAttack
        5.0f, // baseDefense
        7.0f, // baseSpecialDefense
        6.0f, // baseAccuracy
        7.0f, // baseEvasion
        5.5f, // baseSpeed
        21};

    MonsterType nyarlapup = {
        22,
        ELDRITCH,
        "Nyarlapup",
        8.5f, // baseHealth
        5.0f, // baseAttack
        8.0f, // baseSpecialAttack
        4.5f, // baseDefense
        6.5f, // baseSpecialDefense
        5.5f, // baseAccuracy
        7.5f, // baseEvasion
        6.0f, // baseSpeed
        22};

    MonsterType shogghorn = {
        23,
        ELDRITCH,
        "Shogghorn",
        10.5f, // baseHealth
        7.5f,  // baseAttack
        7.5f,  // baseSpecialAttack
        6.5f,  // baseDefense
        8.0f,  // baseSpecialDefense
        5.0f,  // baseAccuracy
        5.5f,  // baseEvasion
        5.0f,  // baseSpeed
        23};

    MonsterType azatheon = {
        24,
        ELDRITCH,
        "Azatheon",
        11.0f, // baseHealth
        6.0f,  // baseAttack
        9.5f,  // baseSpecialAttack
        7.0f,  // baseDefense
        9.5f,  // baseSpecialDefense
        6.0f,  // baseAccuracy
        5.0f,  // baseEvasion
        4.5f,  // baseSpeed
        24};

    // =========================
    // DEMONIC
    // =========================
    MonsterType hellhound = {
        25,
        DEMONIC,
        "Hellhound",
        9.0f, // baseHealth
        9.0f, // baseAttack
        6.5f, // baseSpecialAttack
        5.5f, // baseDefense
        5.0f, // baseSpecialDefense
        7.0f, // baseAccuracy
        7.5f, // baseEvasion
        8.0f, // baseSpeed
        25};

    MonsterType infernalimp = {
        26,
        DEMONIC,
        "Infernalimp",
        7.0f, // baseHealth
        8.5f, // baseAttack
        7.5f, // baseSpecialAttack
        4.5f, // baseDefense
        4.0f, // baseSpecialDefense
        7.5f, // baseAccuracy
        8.0f, // baseEvasion
        8.5f, // baseSpeed
        26};

    MonsterType malgarg = {
        27,
        DEMONIC,
        "Malgarg",
        10.0f, // baseHealth
        9.5f,  // baseAttack
        6.0f,  // baseSpecialAttack
        5.0f,  // baseDefense
        5.5f,  // baseSpecialDefense
        6.0f,  // baseAccuracy
        6.0f,  // baseEvasion
        7.0f,  // baseSpeed
        27};

    MonsterType souldevourer = {
        28,
        DEMONIC,
        "Souldevourer",
        8.5f, // baseHealth
        8.0f, // baseAttack
        7.0f, // baseSpecialAttack
        4.5f, // baseDefense
        4.5f, // baseSpecialDefense
        6.5f, // baseAccuracy
        7.0f, // baseEvasion
        8.5f, // baseSpeed
        28};

    // =========================
    // DIVINE
    // =========================
    MonsterType angelion = {
        29,
        DIVINE,
        "Angelion",
        10.0f, // baseHealth
        6.0f,  // baseAttack
        8.5f,  // baseSpecialAttack
        8.0f,  // baseDefense
        9.0f,  // baseSpecialDefense
        8.0f,  // baseAccuracy
        6.5f,  // baseEvasion
        7.0f,  // baseSpeed
        29};

    MonsterType serapion = {
        30,
        DIVINE,
        "Serapion",
        11.0f, // baseHealth
        5.5f,  // baseAttack
        9.0f,  // baseSpecialAttack
        9.0f,  // baseDefense
        9.5f,  // baseSpecialDefense
        7.5f,  // baseAccuracy
        6.0f,  // baseEvasion
        6.0f,  // baseSpeed
        30};

    MonsterType radiantis = {
        31,
        DIVINE,
        "Radiantis",
        9.0f,  // baseHealth
        5.0f,  // baseAttack
        10.0f, // baseSpecialAttack
        7.5f,  // baseDefense
        8.5f,  // baseSpecialDefense
        8.5f,  // baseAccuracy
        7.0f,  // baseEvasion
        7.5f,  // baseSpeed
        31};

    MonsterType sanctidrae = {
        32,
        DIVINE,
        "Sanctidrae",
        12.0f, // baseHealth
        6.5f,  // baseAttack
        8.0f,  // baseSpecialAttack
        9.0f,  // baseDefense
        8.0f,  // baseSpecialDefense
        7.0f,  // baseAccuracy
        6.0f,  // baseEvasion
        6.5f,  // baseSpeed
        32};

    // =========================
    // ELECTRIC
    // =========================
    MonsterType staticork = {
        33,
        ELECTRIC,
        "Staticork",
        8.0f, // baseHealth
        6.5f, // baseAttack
        8.0f, // baseSpecialAttack
        5.5f, // baseDefense
        6.0f, // baseSpecialDefense
        9.0f, // baseAccuracy
        7.5f, // baseEvasion
        9.5f, // baseSpeed
        33};

    MonsterType stormbather = {
        34,
        ELECTRIC,
        "Stormbather",
        9.0f, // baseHealth
        7.0f, // baseAttack
        8.5f, // baseSpecialAttack
        6.5f, // baseDefense
        7.0f, // baseSpecialDefense
        8.5f, // baseAccuracy
        7.0f, // baseEvasion
        9.0f, // baseSpeed
        34};

    MonsterType ampbeetle = {
        35,
        ELECTRIC,
        "Ampbeetle",
        10.0f, // baseHealth
        5.0f,  // baseAttack
        8.0f,  // baseSpecialAttack
        7.0f,  // baseDefense
        7.5f,  // baseSpecialDefense
        7.0f,  // baseAccuracy
        6.5f,  // baseEvasion
        8.0f,  // baseSpeed
        35};

    MonsterType thunderpole = {
        36,
        ELECTRIC,
        "Thunderpole",
        11.0f, // baseHealth
        8.0f,  // baseAttack
        7.5f,  // baseSpecialAttack
        6.0f,  // baseDefense
        6.5f,  // baseSpecialDefense
        8.0f,  // baseAccuracy
        7.0f,  // baseEvasion
        8.5f,  // baseSpeed
        36};

    // =========================
    // DRAGON
    // =========================
    MonsterType drakenroost = {
        37,
        DRAGON,
        "Drakenroost",
        12.0f, // baseHealth
        9.0f,  // baseAttack
        8.0f,  // baseSpecialAttack
        8.0f,  // baseDefense
        8.0f,  // baseSpecialDefense
        7.5f,  // baseAccuracy
        6.5f,  // baseEvasion
        7.5f,  // baseSpeed
        37};

    MonsterType wyrmling = {
        38,
        DRAGON,
        "Wyrmling",
        8.0f, // baseHealth
        7.0f, // baseAttack
        7.5f, // baseSpecialAttack
        6.5f, // baseDefense
        6.5f, // baseSpecialDefense
        6.5f, // baseAccuracy
        7.0f, // baseEvasion
        7.0f, // baseSpeed
        38};

    MonsterType basilisk = {
        39,
        DRAGON,
        "Basilisk",
        11.0f, // baseHealth
        8.5f,  // baseAttack
        7.0f,  // baseSpecialAttack
        8.5f,  // baseDefense
        7.5f,  // baseSpecialDefense
        7.0f,  // baseAccuracy
        6.5f,  // baseEvasion
        6.5f,  // baseSpeed
        39};

    MonsterType wyvern = {
        40,
        DRAGON,
        "Wyvern",
        10.0f, // baseHealth
        8.0f,  // baseAttack
        8.5f,  // baseSpecialAttack
        7.0f,  // baseDefense
        7.0f,  // baseSpecialDefense
        7.5f,  // baseAccuracy
        7.0f,  // baseEvasion
        8.0f,  // baseSpeed
        40};

    // =========================
    // PSYCHIC
    // =========================
    MonsterType mindraker = {
        41,
        PSYCHIC,
        "Mindraker",
        9.0f, // baseHealth
        5.0f, // baseAttack
        9.5f, // baseSpecialAttack
        6.0f, // baseDefense
        7.0f, // baseSpecialDefense
        8.0f, // baseAccuracy
        7.5f, // baseEvasion
        7.0f, // baseSpeed
        41};

    MonsterType astromoth = {
        42,
        PSYCHIC,
        "Astromoth",
        8.5f,  // baseHealth
        4.5f,  // baseAttack
        10.0f, // baseSpecialAttack
        5.5f,  // baseDefense
        7.5f,  // baseSpecialDefense
        8.0f,  // baseAccuracy
        7.0f,  // baseEvasion
        7.5f,  // baseSpeed
        42};

    MonsterType telephant = {
        43,
        PSYCHIC,
        "Telephant",
        11.0f, // baseHealth
        6.0f,  // baseAttack
        8.5f,  // baseSpecialAttack
        7.5f,  // baseDefense
        7.5f,  // baseSpecialDefense
        7.5f,  // baseAccuracy
        5.5f,  // baseEvasion
        6.0f,  // baseSpeed
        43};

    MonsterType clairvoxa = {
        44,
        PSYCHIC,
        "Clairvoxa",
        10.0f, // baseHealth
        5.5f,  // baseAttack
        9.0f,  // baseSpecialAttack
        6.5f,  // baseDefense
        8.0f,  // baseSpecialDefense
        7.0f,  // baseAccuracy
        7.0f,  // baseEvasion
        7.0f,  // baseSpeed
        44};

    // =========================
    // FIGHTING
    // =========================
    MonsterType pumafist = {
        45,
        FIGHTING,
        "Pumafist",
        9.0f, // baseHealth
        9.0f, // baseAttack
        4.5f, // baseSpecialAttack
        6.5f, // baseDefense
        6.0f, // baseSpecialDefense
        8.0f, // baseAccuracy
        7.5f, // baseEvasion
        8.0f, // baseSpeed
        45};

    MonsterType fistape = {
        46,
        FIGHTING,
        "Fistape",
        10.0f, // baseHealth
        8.5f,  // baseAttack
        5.0f,  // baseSpecialAttack
        7.0f,  // baseDefense
        7.0f,  // baseSpecialDefense
        7.5f,  // baseAccuracy
        6.5f,  // baseEvasion
        7.5f,  // baseSpeed
        46};

    MonsterType brawligator = {
        47,
        FIGHTING,
        "Brawligator",
        12.0f, // baseHealth
        9.5f,  // baseAttack
        4.0f,  // baseSpecialAttack
        8.0f,  // baseDefense
        7.5f,  // baseSpecialDefense
        6.0f,  // baseAccuracy
        5.5f,  // baseEvasion
        6.5f,  // baseSpeed
        47};

    MonsterType thundermonk = {
        48,
        FIGHTING,
        "Thundermonk",
        8.0f, // baseHealth
        8.0f, // baseAttack
        5.5f, // baseSpecialAttack
        6.0f, // baseDefense
        5.5f, // baseSpecialDefense
        8.0f, // baseAccuracy
        7.0f, // baseEvasion
        8.0f, // baseSpeed
        48};

    // =========================
    // NORMAL
    // =========================
    MonsterType mushape = {
        49,
        NORMAL,
        "Mushape",
        10.0f, // baseHealth
        6.0f,  // baseAttack
        6.0f,  // baseSpecialAttack
        6.0f,  // baseDefense
        6.0f,  // baseSpecialDefense
        7.0f,  // baseAccuracy
        6.5f,  // baseEvasion
        6.5f,  // baseSpeed
        49};

    MonsterType armaduff = {
        50,
        NORMAL,
        "Armaduff",
        11.0f, // baseHealth
        7.0f,  // baseAttack
        5.0f,  // baseSpecialAttack
        7.5f,  // baseDefense
        7.0f,  // baseSpecialDefense
        6.5f,  // baseAccuracy
        6.0f,  // baseEvasion
        5.5f,  // baseSpeed
        50};

    MonsterType kangaroost = {
        51,
        NORMAL,
        "Kangaroost",
        9.0f, // baseHealth
        7.5f, // baseAttack
        5.5f, // baseSpecialAttack
        6.5f, // baseDefense
        6.0f, // baseSpecialDefense
        7.5f, // baseAccuracy
        7.0f, // baseEvasion
        6.5f, // baseSpeed
        51};

    MonsterType equinix = {
        52,
        NORMAL,
        "Equinix",
        10.0f, // baseHealth
        6.5f,  // baseAttack
        5.5f,  // baseSpecialAttack
        6.0f,  // baseDefense
        6.5f,  // baseSpecialDefense
        7.0f,  // baseAccuracy
        6.0f,  // baseEvasion
        7.0f,  // baseSpeed
        52};

    monsterTypes[1] = phoenix;
    monsterTypes[2] = leviathan;
    monsterTypes[3] = golem;
    monsterTypes[4] = sylph;
}