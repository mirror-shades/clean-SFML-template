#include "environment.h"
#include <random>
#include "elements.h"

void Environment::determineLevelElement(ElementType levelElement)
{
    // get a random number and choose a random type of element from element.h
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(ElementType::ELDRITCH));
    levelElement = static_cast<ElementType>(dis(gen));
}

ElementType Environment::getLevelElement()
{
    return levelElement;
}

std::string Environment::getLevelElementString()
{
    static const std::map<ElementType, std::string> elementNames = {
        {ElementType::FIRE, "Fire"},
        {ElementType::WATER, "Water"},
        {ElementType::EARTH, "Earth"},
        {ElementType::AIR, "Air"},
        {ElementType::NORMAL, "Normal"},
        {ElementType::ELECTRIC, "Electric"},
        {ElementType::FIGHTING, "Fighting"},
        {ElementType::PSYCHIC, "Psychic"},
        {ElementType::DIVINE, "Divine"},
        {ElementType::CYBERNETIC, "Cybernetic"},
        {ElementType::DRAGON, "Dragon"},
        {ElementType::DEMONIC, "Demonic"},
        {ElementType::ELDRITCH, "Eldritch"},
    };

    auto it = elementNames.find(levelElement);
    return it != elementNames.end() ? it->second : "Unknown";
}

std::vector<Monster> &Environment::getEnemyMonsters()
{
    return enemyMonsters;
}

void Environment::addEnemyMonster(Monster monster)
{
    enemyMonsters.push_back(monster);
}

void Environment::removeEnemyMonster(Monster monster)
{
    for (auto it = enemyMonsters.begin(); it != enemyMonsters.end(); ++it)
    {
        if (it->id == monster.id &&
            it->name == monster.name &&
            it->element == monster.element)
        {
            enemyMonsters.erase(it);
            break;
        }
    }
}

void Environment::clearEnemyMonsters()
{
    enemyMonsters.clear();
}

void Environment::updateEnemyMonsters(std::vector<Monster> newMonsters)
{
    enemyMonsters = newMonsters;
}
