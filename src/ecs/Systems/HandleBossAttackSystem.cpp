/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system handling Boss Attacks methods
*/

#include "HandleBossAttackSystem.hh"

RType::HandleBossAttackSystem::HandleBossAttackSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient):
    ASystem(S_BOSS_ATTACK, addEntity, deleteEntity), _sendMessageToAllClient(sendMessageToAllClient)
{
}

RType::HandleBossAttackSystem::~HandleBossAttackSystem()
{
}

void RType::HandleBossAttackSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    auto attack = entity->getComponent<AttackComponent>();
    auto health = entity->getComponent<HealthComponent>();
    auto clock = entity->getComponent<ClockComponent>();
    auto interval = entity->getComponent<ShootIntervalComponent>();
    float healthPercentage = static_cast<float>(health->getHealth()) / health->getMaxHealth();

    std::size_t numberOfPatterns = attack->getNumberOfPattern();
    std::size_t currentPatternIndex = attack->getCurrentPatternIndex();

    for (std::size_t i = 1; i < numberOfPatterns; i++) {
        float limitHealth = 1.0 - static_cast<float>(i) / numberOfPatterns;

        if (healthPercentage <= limitHealth && currentPatternIndex < i) {
            attack->nextAttackPattern();
            currentPatternIndex++;
        }
    }

    if (clock->getClock(SHOOTING_CLOCK).getElapsedTime().asSeconds() > interval->getShootInterval()) {
        attack->executeCurrentAttackPattern(entity, _addEntity, _sendMessageToAllClient);
        clock->getClock(SHOOTING_CLOCK).restart();
    }
}

bool RType::HandleBossAttackSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::AttackComponent>() == nullptr
    || entity->getComponent<RType::HealthComponent>() == nullptr
    || entity->getComponent<RType::ShootIntervalComponent>() == nullptr
    || entity->getComponent<RType::ClockComponent>() == nullptr
    ) {
        return false;
    }
    return (true);
}