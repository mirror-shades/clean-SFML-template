#include "battle.h"
#include <random>
#include <chrono>
#include <thread>
#include <sstream>
#include <iostream>
#include "types.h"
#include "render.h"

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

void Battle::executeAIMove(Monster &attacker, std::vector<Monster> &playerTeam, std::vector<Monster> &enemyTeam)
{
    // Combine both teams into a single vector for targeting
    std::vector<Monster> allMonsters;
    allMonsters.insert(allMonsters.end(), playerTeam.begin(), playerTeam.end());
    allMonsters.insert(allMonsters.end(), enemyTeam.begin(), enemyTeam.end());

    // Find attacker index in combined vector
    int attackerIndex = -1;
    for (size_t i = 0; i < allMonsters.size(); i++)
    {
        if (allMonsters[i].currentStats.uid == attacker.currentStats.uid)
        {
            attackerIndex = i;
            break;
        }
    }

    if (attackerIndex == -1)
    {
        std::cout << "Error: Attacker not found in combined team vector!" << std::endl;
        return;
    }

    // Get valid targets based on move's targeting type
    std::vector<Monster *> validTargets;
    for (size_t i = 0; i < allMonsters.size(); i++)
    {
        Monster &target = allMonsters[i];
        if (target.currentStats.health > 0 && target.currentStats.faction != attacker.currentStats.faction)
        {
            validTargets.push_back(&allMonsters[i]);
        }
    }

    if (validTargets.empty())
        return;

    // For AI, randomly select one target if it's a single-target move
    if (attacker.currentStats.moves[0].targetType == TargetType::SINGLE_ENEMY)
    {
        // Optionally find a "best" target (for demonstration, we check type effectiveness)
        Monster *bestTarget = nullptr;
        float bestEffectiveness = 0.0f;

        for (auto *possibleTarget : validTargets)
        {
            float effectiveness = getTypeEffectiveness(attacker.currentStats.moves[0].element,
                                                       possibleTarget->currentStats.element);
            if (effectiveness > bestEffectiveness)
            {
                bestEffectiveness = effectiveness;
                bestTarget = possibleTarget;
            }
        }

        // If a best target was found, use it; otherwise pick randomly
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

    // Create a BattleTurn to record in history
    BattleTurn turn;
    turn.attackerId = attacker.currentStats.id;
    turn.targetIds.clear();
    for (const auto &target : validTargets)
    {
        turn.targetIds.push_back(target->currentStats.id);
    }
    turn.action = attacker.currentStats.moves[0].name;

    // Execute the move on all valid targets
    for (auto *target : validTargets)
    {
        // Find target index in combined vector
        int targetIndex = -1;
        for (size_t i = 0; i < allMonsters.size(); i++)
        {
            if (allMonsters[i].currentStats.uid == target->currentStats.uid)
            {
                targetIndex = i;
                break;
            }
        }

        if (targetIndex == -1)
            continue;

        // ======================
        // ACCURACY CHECK
        // ======================
        const Move &move = attacker.currentStats.moves[0];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> accuracy_roll(1, 100);
        int roll = accuracy_roll(gen);

        if (roll > move.accuracy)
        {
            // ==================
            // MOVE MISSED
            // ==================
            std::cout << "BATTLE EXECUTEAIMOVE: Move missed!" << std::endl;
            if (onAnimationRequested)
            {
                // 1. Choose attack animation based on faction
                AnimationState attackAnim = (attacker.currentStats.faction == Faction::PLAYER)
                                                ? AnimationState::ATTACK_RIGHT
                                                : AnimationState::ATTACK_LEFT;

                // 2. Attacker does the attack animation (but it misses)
                onAnimationRequested(attackAnim, attackerIndex, targetIndex, 0.5f);

                // 3. Small delay, then return attacker to idle
                onAnimationRequested(AnimationState::IDLE, attackerIndex, targetIndex, 0.2f);
            }
        }
        else
        {
            // ==================
            // MOVE HIT
            // ==================
            if (onAnimationRequested)
            {
                // 1. Choose attack animation based on faction
                AnimationState attackAnim = (attacker.currentStats.faction == Faction::PLAYER)
                                                ? AnimationState::ATTACK_RIGHT
                                                : AnimationState::ATTACK_LEFT;

                // 2. Attacker does the attack animation
                // If it's an enemy (right side), adjust the index
                int sourceIndex = attackerIndex;
                if (attacker.currentStats.faction == Faction::ENEMY)
                {
                    sourceIndex = attackerIndex - playerTeam.size();
                }

                // If target is an enemy, adjust the target index
                int defenderIndex = targetIndex;
                if (target->currentStats.faction == Faction::ENEMY)
                {
                    defenderIndex = targetIndex - playerTeam.size();
                }

                onAnimationRequested(attackAnim, sourceIndex, defenderIndex, 0.3f);
                onAnimationRequested(AnimationState::DEFENDING, defenderIndex, defenderIndex, 0.3f);
                onAnimationRequested(AnimationState::IDLE, sourceIndex, defenderIndex, 0.2f);
            }

            // ==================
            // DAMAGE CALCULATION
            // ==================
            float typeModifier = getTypeEffectiveness(move.element, target->currentStats.element);

            int attackStat = (move.type == MoveType::SPECIAL)
                                 ? attacker.currentStats.specialAttack
                                 : attacker.currentStats.attack;
            int defenseStat = (move.type == MoveType::SPECIAL)
                                  ? target->currentStats.specialDefense
                                  : target->currentStats.defense;

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
                damage = static_cast<int>(damage * 1.4f);
            }

            int oldHealth = target->currentStats.health;
            target->currentStats.health = std::max(0, target->currentStats.health - damage);

            // ==================
            // LOGGING RESULTS
            // ==================
            std::string attackerFaction = (attacker.currentStats.faction == Faction::PLAYER) ? "Allied" : "Enemy";
            std::string targetFaction = (target->currentStats.faction == Faction::PLAYER) ? "Allied" : "Enemy";

            std::stringstream result;
            result << attackerFaction << " " << attacker.currentStats.name
                   << " used " << move.moveName << " on "
                   << targetFaction << " " << target->currentStats.name << "! ";

            if (isCritical)
                result << "Critical hit! ";
            if (typeModifier > 1.0f)
                result << "It's super effective! ";
            if (typeModifier < 1.0f)
                result << "It's not very effective... ";

            result << "Deals " << damage << " damage to " << targetFaction << " "
                   << target->currentStats.name;

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
