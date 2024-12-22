#include "monster.h"
#include <random>

Monster MonsterManager::createMonster(const MonsterType &baseType)
{
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
    monster.attack = static_cast<int>(baseType.baseAttack * dis(gen) * 10);
    monster.specialAttack = static_cast<int>(baseType.baseSpecialAttack * dis(gen) * 10);
    monster.defense = static_cast<int>(baseType.baseDefense * dis(gen) * 10);
    monster.specialDefense = static_cast<int>(baseType.baseSpecialDefense * dis(gen) * 10);
    monster.magic = static_cast<int>(baseType.baseMagic * dis(gen) * 10);
    monster.accuracy = static_cast<int>(baseType.baseAccuracy * dis(gen) * 10);
    monster.evasion = static_cast<int>(baseType.baseEvasion * dis(gen) * 10);
    monster.speed = static_cast<int>(baseType.baseSpeed * dis(gen) * 10);

    return monster;
}
