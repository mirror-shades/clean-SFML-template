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
