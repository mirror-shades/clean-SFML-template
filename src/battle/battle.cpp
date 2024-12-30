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
    if (attacker.currentStats.health <= 0)
        return;

    const Move &move = attacker.currentStats.moves[0]; // Still need to implement move selection
    std::vector<Monster *> validTargets;

    // Get valid targets based on move's targeting type
    for (size_t i = 0; i < targets.size(); i++)
    {
        Monster &target = targets[i]; // Get direct reference to vector element
        if (target.currentStats.health > 0 && target.currentStats.faction != attacker.currentStats.faction)
        {
            validTargets.push_back(&targets[i]); // Store pointer to actual vector element
        }
    }

    // If no valid targets, end turn
    if (validTargets.empty())
        return;

    // For AI, randomly select one target if it's a single-target move
    if (move.targetType == TargetType::SINGLE_ENEMY)
    {
        // Find the target that would take the most damage
        Monster *bestTarget = nullptr;
        float bestEffectiveness = 0.0f;

        for (auto *possibleTarget : validTargets)
        {
            float effectiveness = getTypeEffectiveness(move.element, possibleTarget->currentStats.element);
            if (effectiveness > bestEffectiveness)
            {
                bestEffectiveness = effectiveness;
                bestTarget = possibleTarget;
            }
        }

        // If we found a target, use it. Otherwise, keep random selection
        if (bestTarget != nullptr)
        {
            validTargets = {bestTarget};
        }
        else
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, validTargets.size() - 1);
            Monster *selected = validTargets[dist(gen)];
            validTargets = {selected};
        }
    }

    // Create turn info
    BattleTurn turn;
    turn.attackerId = attacker.currentStats.id;
    turn.targetIds.clear();
    for (const auto &target : validTargets)
    {
        turn.targetIds.push_back(target->currentStats.id);
    }
    turn.action = move.name;

    // Execute move on all valid targets
    for (auto *target : validTargets)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> accuracy_roll(1, 100);
        int roll = accuracy_roll(gen);

        if (roll > move.accuracy)
        {
            std::string result = attacker.currentStats.name + "'s " + move.moveName + " missed!";
            turn.result = result;
            addTurn(turn);
        }
        else
        {
            float typeModifier = getTypeEffectiveness(move.element, target->currentStats.element);

            int attackStat = (move.type == MoveType::SPECIAL) ? attacker.currentStats.specialAttack : attacker.currentStats.attack;
            int defenseStat = (move.type == MoveType::SPECIAL) ? target->currentStats.specialDefense : target->currentStats.defense;

            float baseDamage = (move.power * (attackStat + 10) / (defenseStat + 20)) / 2.5f;
            float stabBonus = (move.element == attacker.currentStats.element) ? 1.4f : 1.0f;

            float modifiedDamage = baseDamage * typeModifier * stabBonus;

            float random = 0.9f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.3f)));
            modifiedDamage *= random;

            int damage = std::round(modifiedDamage);

            int critRoll = accuracy_roll(gen);
            bool isCritical = (critRoll <= 10);

            if (isCritical)
            {
                damage *= 1.4;
            }

            int oldHealth = target->currentStats.health;
            target->currentStats.health = std::max(0, target->currentStats.health - damage);

            std::string attackerFaction = (attacker.currentStats.faction == Faction::PLAYER) ? "Allied" : "Enemy";
            std::string targetFaction = (target->currentStats.faction == Faction::PLAYER) ? "Allied" : "Enemy";

            std::stringstream result;
            result << attackerFaction << " " << attacker.currentStats.name << " used " << move.moveName << " on "
                   << targetFaction << " " << target->currentStats.name << "! ";
            if (isCritical)
                result << "Critical hit! ";
            if (typeModifier > 1.0f)
                result << "It's super effective! ";
            if (typeModifier < 1.0f)
                result << "It's not very effective... ";
            result << "Deals " << damage << " damage to " << targetFaction << " " << target->currentStats.name;

            turn.result = result.str();
            addTurn(turn);
            std::cout << turn.result << "\n";
            std::cout << oldHealth << " -> " << target->currentStats.health << std::endl;
        }
    }
}

float Battle::getTypeEffectiveness(ElementType moveType, ElementType targetType)
{
    static const float typeChart[12][12] = {
        // FIRE  WATER EARTH AIR   DIVINE ELDRITCH DEMONIC CYBER FIGHT PSYCHIC DRAGON ELECTRIC
        {0.7f, 0.7f, 1.4f, 1.0f, 1.0f, 1.0f, 1.4f, 1.0f, 1.4f, 1.0f, 0.7f, 1.0f}, // FIRE
        {1.4f, 0.7f, 1.0f, 0.7f, 1.4f, 1.0f, 1.0f, 1.0f, 1.0f, 1.4f, 1.0f, 0.7f}, // WATER
        {0.7f, 1.0f, 0.7f, 1.4f, 1.0f, 1.0f, 1.0f, 1.4f, 0.7f, 1.0f, 1.0f, 1.4f}, // EARTH
        {1.0f, 1.4f, 0.7f, 0.7f, 1.0f, 1.4f, 1.0f, 1.0f, 1.0f, 0.7f, 1.4f, 1.0f}, // AIR
        {1.0f, 1.4f, 1.0f, 1.0f, 0.7f, 0.7f, 1.4f, 1.0f, 1.0f, 1.0f, 1.0f, 1.4f}, // DIVINE
        {1.0f, 1.0f, 1.0f, 1.4f, 1.4f, 0.7f, 1.0f, 0.7f, 1.4f, 1.0f, 1.0f, 1.0f}, // ELDRITCH
        {1.4f, 1.0f, 1.0f, 1.0f, 0.7f, 1.0f, 0.7f, 1.4f, 1.0f, 1.0f, 1.4f, 1.0f}, // DEMONIC
        {1.0f, 1.0f, 1.4f, 1.0f, 1.0f, 1.4f, 0.7f, 0.7f, 1.0f, 1.4f, 1.0f, 1.0f}, // CYBERNETIC
        {0.7f, 1.0f, 1.0f, 1.0f, 1.4f, 1.0f, 1.0f, 1.4f, 1.4f, 0.7f, 1.0f, 1.4f}, // FIGHTING
        {1.0f, 1.0f, 1.0f, 0.7f, 1.0f, 1.4f, 1.4f, 1.0f, 0.7f, 1.4f, 1.4f, 1.0f}, // PSYCHIC
        {1.0f, 1.0f, 1.0f, 0.7f, 1.4f, 1.4f, 1.0f, 1.0f, 1.0f, 1.4f, 1.4f, 0.7f}, // DRAGON
        {1.0f, 0.7f, 1.0f, 1.0f, 1.0f, 1.0f, 1.4f, 1.4f, 1.4f, 1.0f, 0.7f, 1.4f}  // ELECTRIC
    };

    return typeChart[static_cast<int>(moveType)][static_cast<int>(targetType)];
}

// Add this function to handle player's move selection
void Battle::executePlayerMove(Monster &attacker, Monster &target, int moveIndex)
{
    // Get the selected move
    if (moveIndex >= 0 && moveIndex < attacker.currentStats.moves.size())
    {
        Move &selectedMove = attacker.currentStats.moves[moveIndex];

        // Calculate damage based on move power, attacker's stats, and target's defense
        int damage = calculateMoveDamage(attacker, target, selectedMove);
        target.currentStats.health = std::max(0, target.currentStats.health - damage);

        // Reset the monster's action flag
        attacker.turnPoints = 0;
        attacker.movePoints -= selectedMove.moveCost;
    }
}

int Battle::calculateMoveDamage(const Monster &attacker, const Monster &target, const Move &move)
{
    int attackStat = (move.type == MoveType::SPECIAL) ? attacker.currentStats.specialAttack : attacker.currentStats.attack;
    int defenseStat = (move.type == MoveType::SPECIAL) ? target.currentStats.specialDefense : target.currentStats.defense;

    // Reduced attack scaling and increased defense impact
    float baseDamage = (move.power * (attackStat + 10) / (defenseStat + 15));

    float typeMultiplier = getTypeEffectiveness(move.element, target.currentStats.element);
    typeMultiplier = std::pow(typeMultiplier, 1.4);

    float random = 0.9f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.3f)));
    float stabBonus = (move.element == attacker.currentStats.element) ? 1.4f : 1.0f;

    return std::max(1, static_cast<int>(baseDamage * typeMultiplier * random * stabBonus));
}

void Battle::deinit(Player &player)
{
    battleHistory.clear();
    restoreMonsters(player);
}

void Battle::restoreMonsters(Player &player)
{
    std::vector<Monster> playerMonsters = player.getActiveMonsters();
    for (Monster &monster : playerMonsters)
    {
        monster.currentStats = monster.baseStats;
    }
}
