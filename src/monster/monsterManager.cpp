#include <random>
#include <iostream>
#include "monsterManager.h"
#include "monster.h"
#include "moves.h"
#include "elements.h"

Monster MonsterManager::createMonster(int type)
{
    MonsterType baseType = monsterTypes[type];
    // Create random number generator for values between 0.9 and 1.0
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.9f, 1.0f);

    Monster monster;
    monster.id = baseType.id;
    monster.element = baseType.element;
    monster.name = baseType.name;

    // Multiply base stats by random multiplier and round to integer
    monster.health = static_cast<int>(baseType.baseHealth * dis(gen) * 10);
    monster.currentHealth = monster.health;
    monster.attack = static_cast<int>(baseType.baseAttack * dis(gen) * 10);
    monster.specialAttack = static_cast<int>(baseType.baseSpecialAttack * dis(gen) * 10);
    monster.defense = static_cast<int>(baseType.baseDefense * dis(gen) * 10);
    monster.specialDefense = static_cast<int>(baseType.baseSpecialDefense * dis(gen) * 10);
    monster.magic = static_cast<int>(baseType.baseMagic * dis(gen) * 10);
    monster.accuracy = static_cast<int>(baseType.baseAccuracy * dis(gen) * 10);
    monster.evasion = static_cast<int>(baseType.baseEvasion * dis(gen) * 10);
    monster.speed = static_cast<int>(baseType.baseSpeed * dis(gen) * 10);
    monster.currentTurnPoints = 0;
    monster.currentMovePoints = 0;
    monster.moves.push_back(moveTypes[baseType.initialMove]);

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
    std::cout << "Monster: " << monster.name << std::endl;
    std::cout << "Health: " << monster.health << std::endl;
    std::cout << "Attack: " << monster.attack << std::endl;
    std::cout << "Special Attack: " << monster.specialAttack << std::endl;
    std::cout << "Defense: " << monster.defense << std::endl;
    std::cout << "Special Defense: " << monster.specialDefense << std::endl;
    std::cout << "Magic: " << monster.magic << std::endl;
    std::cout << "Accuracy: " << monster.accuracy << std::endl;
    std::cout << "Evasion: " << monster.evasion << std::endl;
    std::cout << "Speed: " << monster.speed << std::endl;
    for (Move move : monster.moves)
    {
        std::cout << "Move: " << move.name << std::endl;
    }
}
