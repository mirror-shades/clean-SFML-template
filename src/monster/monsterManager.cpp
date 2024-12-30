#include <random>
#include <iostream>
#include "monsterManager.h"
#include "monster.h"
#include "types.h"

Monster MonsterManager::createMonster(int type, Faction faction)
{
    MonsterType baseType = monsterTypes[type];
    // Create random number generator for values between 0.9 and 1.0
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.9f, 1.0f);

    BaseMonster baseStats;
    baseStats.id = baseType.id;
    baseStats.element = baseType.element;
    baseStats.name = baseType.name;

    // Multiply base stats by random multiplier and round to integer
    baseStats.health = static_cast<int>(baseType.baseHealth * dis(gen) * 15 + 50);
    baseStats.attack = static_cast<int>(baseType.baseAttack * dis(gen) * 10);
    baseStats.specialAttack = static_cast<int>(baseType.baseSpecialAttack * dis(gen) * 10);
    baseStats.defense = static_cast<int>(baseType.baseDefense * dis(gen) * 10);
    baseStats.specialDefense = static_cast<int>(baseType.baseSpecialDefense * dis(gen) * 10);
    baseStats.accuracy = static_cast<int>(baseType.baseAccuracy * dis(gen) * 10);
    baseStats.evasion = static_cast<int>(baseType.baseEvasion * dis(gen) * 10);
    baseStats.speed = static_cast<int>(baseType.baseSpeed * dis(gen) * 10);
    baseStats.moves.push_back(moveTypes[baseType.initialMove]);
    baseStats.uid = totalMonsters;
    baseStats.faction = faction;

    Monster monster(baseStats);

    totalMonsters++;
    return monster;
}

void MonsterManager::initializeMonsterTypes()
{
    ::initializeMonsterTypes();
}

void MonsterManager::initializeMoveTypes()
{
    ::initializeMoveTypes();
}

void MonsterManager::printMonster(Monster monster)
{
    std::cout << "Monster: " << monster.baseStats.name << std::endl;
    std::cout << "Health: " << monster.baseStats.health << std::endl;
    std::cout << "Attack: " << monster.baseStats.attack << std::endl;
    std::cout << "Special Attack: " << monster.baseStats.specialAttack << std::endl;
    std::cout << "Defense: " << monster.baseStats.defense << std::endl;
    std::cout << "Special Defense: " << monster.baseStats.specialDefense << std::endl;
    std::cout << "Accuracy: " << monster.baseStats.accuracy << std::endl;
    std::cout << "Evasion: " << monster.baseStats.evasion << std::endl;
    std::cout << "Speed: " << monster.baseStats.speed << std::endl;
    for (Move move : monster.baseStats.moves)
    {
        std::cout << "Move: " << move.moveName << std::endl;
    }
}
