#include "battle.h"
#include <random>
#include <chrono>
#include <thread>
#include <sstream>
#include <iostream>

void Battle::addTurn(BattleTurn turn)
{
    battleHistory.push_back(turn);
}

void Battle::clearBattleHistory()
{
    battleHistory.clear();
}

BattleTurn Battle::getLastTurn()
{
    return battleHistory.back();
}

std::vector<BattleTurn> Battle::getBattleHistory()
{
    return battleHistory;
}

void Battle::executeAIMove(Monster &attacker, std::vector<Monster> &targets)
{
    if (attacker.currentHealth <= 0)
    {
        return;
    }

    auto validTarget = std::find_if(targets.begin(), targets.end(),
                                    [&attacker](const Monster &m)
                                    {
                                        return m.currentHealth > 0 &&
                                               m.faction != attacker.faction;
                                    });

    if (validTarget != targets.end())
    {
        Monster &target = *validTarget;
        const Move &move = attacker.moves[0]; // fix this

        if (attacker.moves.empty())
        {
            std::cout << "ERROR: Attacker has no moves! this should not happen.\n";
            return;
        }

        BattleTurn turn;
        turn.attackerId = attacker.id;
        turn.targetIds = {target.id};
        turn.action = move.name;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> accuracy_roll(1, 100);
        int roll = accuracy_roll(gen);

        if (roll > move.accuracy)
        {
            std::string result = attacker.name + "'s " + move.moveName + " missed!";
            turn.result = result;
            addTurn(turn);
        }
        else
        {
            float typeModifier = getTypeEffectiveness(move.element, target.element);

            int baseDamage = std::max(1, (attacker.attack * move.power / 100) - (target.defense / 2));

            int damage = std::round(baseDamage * typeModifier);

            int critRoll = accuracy_roll(gen);
            bool isCritical = (critRoll <= 5);

            if (isCritical)
            {
                damage *= 2;
            }

            int oldHealth = target.currentHealth;
            target.currentHealth = std::max(0, target.currentHealth - damage);

            std::string attackerFaction = (attacker.faction == Faction::PLAYER) ? "Allied" : "Enemy";
            std::string targetFaction = (target.faction == Faction::PLAYER) ? "Allied" : "Enemy";
            std::stringstream result;
            result << attackerFaction << " " << attacker.name << " used " << move.name << " on " << targetFaction << " " << target.name << "! ";
            if (isCritical)
                result << "Critical hit! ";
            if (typeModifier > 1.0f)
                result << "It's super effective! ";
            if (typeModifier < 1.0f)
                result << "It's not very effective... ";
            result << "Deals " << damage << " damage to " << targetFaction << " " << target.name;

            turn.result = result.str();
            addTurn(turn);

            std::cout << turn.result << "\n";
        }

        // IMPORTANT: Consume turn points
        attacker.currentTurnPoints = 0;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

float Battle::getTypeEffectiveness(ElementType moveType, ElementType targetType)
{
    static const float typeChart[12][12] = {
        // FIRE  WATER EARTH AIR   DIVINE ELDRITCH DEMONIC CYBER FIGHT PSYCHIC DRAGON ELECTRIC
        {0.5f, 0.5f, 1.5f, 1.0f, 1.0f, 1.0f, 1.5f, 1.0f, 1.5f, 1.0f, 0.5f, 1.0f}, // FIRE
        {1.5f, 0.5f, 1.0f, 0.5f, 1.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 1.0f, 0.5f}, // WATER
        {0.5f, 1.0f, 0.5f, 1.5f, 1.0f, 1.0f, 1.0f, 1.5f, 0.5f, 1.0f, 1.0f, 1.5f}, // EARTH
        {1.0f, 1.5f, 0.5f, 0.5f, 1.0f, 1.5f, 1.0f, 1.0f, 1.0f, 0.5f, 1.5f, 1.0f}, // AIR
        {1.0f, 1.5f, 1.0f, 1.0f, 0.5f, 0.5f, 1.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f}, // DIVINE
        {1.0f, 1.0f, 1.0f, 1.5f, 1.5f, 0.5f, 1.0f, 0.5f, 1.5f, 1.0f, 1.0f, 1.0f}, // ELDRITCH
        {1.5f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 0.5f, 1.5f, 1.0f, 1.0f, 1.5f, 1.0f}, // DEMONIC
        {1.0f, 1.0f, 1.5f, 1.0f, 1.0f, 1.5f, 0.5f, 0.5f, 1.0f, 1.5f, 1.0f, 1.0f}, // CYBERNETIC
        {0.5f, 1.0f, 1.0f, 1.0f, 1.5f, 1.0f, 1.0f, 1.5f, 1.5f, 0.5f, 1.0f, 1.5f}, // FIGHTING
        {1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.5f, 1.5f, 1.0f, 0.5f, 1.5f, 1.5f, 1.0f}, // PSYCHIC
        {1.0f, 1.0f, 1.0f, 0.5f, 1.5f, 1.5f, 1.0f, 1.0f, 1.0f, 1.5f, 1.5f, 0.5f}, // DRAGON
        {1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 1.5f, 1.5f, 1.0f, 0.5f, 1.5f}  // ELECTRIC
    };

    return typeChart[static_cast<int>(moveType)][static_cast<int>(targetType)];
}

// Add this function to handle player's move selection
void Battle::executePlayerMove(Monster &attacker, Monster &target, int moveIndex)
{
    // Get the selected move
    if (moveIndex >= 0 && moveIndex < attacker.moves.size())
    {
        Move &selectedMove = attacker.moves[moveIndex];

        // Calculate damage based on move power, attacker's stats, and target's defense
        int damage = calculateMoveDamage(attacker, target, selectedMove);
        target.currentHealth = std::max(0, target.currentHealth - damage);

        // Reset the monster's action flag
        attacker.canAct = false;
    }
}

int Battle::calculateMoveDamage(const Monster &attacker, const Monster &target, const Move &move)
{
    // Choose attack and defense stats based on move type
    int attackStat = (move.type == MoveType::SPECIAL) ? attacker.specialAttack : attacker.attack;
    int defenseStat = (move.type == MoveType::SPECIAL) ? target.specialDefense : target.defense;

    // Basic damage formula using appropriate stats
    float baseDamage = move.power * (float)attackStat / defenseStat;

    // Add type effectiveness
    float typeMultiplier = getTypeEffectiveness(move.element, target.element);

    // Add random variation (0.85 to 1.15)
    float random = 0.85f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.3f)));

    return std::max(1, static_cast<int>(baseDamage * typeMultiplier * random));
}