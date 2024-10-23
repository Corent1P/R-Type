/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** system handling direction pattern methods
*/

#include "HandlePatternSystem.hpp"

RType::HandlePatternSystem::HandlePatternSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_PATTERN, addEntity, deleteEntity)
{
}

RType::HandlePatternSystem::~HandlePatternSystem()
{
}
void RType::HandlePatternSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    for (const auto &entity: entities) {
        if (entity->getComponent<EntityTypeComponent>() != nullptr && entity->getComponent<EntityTypeComponent>()->getEntityType() == E_PLAYER)
        {
            for(const auto &entity2: entities) {
                if (verifyRequiredComponent(entity2)) {
                    // if (entity2->getComponent<EntityTypeComponent>() != nullptr && entity2->getComponent<EntityTypeComponent>()->getEntityType() == E_SHIELD) {
                    //     std::cout << "set pattern for Enity Shield" << std::endl;
                    //     entity2->getComponent<DirectionPatternComponent>()->setPattern(sf::Vector2f(entity->getComponent<PositionComponent>()->getPositionX(), entity->getComponent<PositionComponent>()->getPositionY()));
                    // }
                    if (entity2->getComponent<DirectionPatternComponent>()->getPatternType() == FOLLOW_PLAYER) {
                        //std::cout << "set pattern for Enity Shield" << std::endl;
                        entity2->getComponent<DirectionPatternComponent>()->setPattern(sf::Vector2f(
                        entity->getComponent<PositionComponent>()->getPositionX() - (entity2->getComponent<IntRectComponent>()->getIntRectWidth() - entity->getComponent<IntRectComponent>()->getIntRectWidth()),
                        entity->getComponent<PositionComponent>()->getPositionY() - ((entity2->getComponent<IntRectComponent>()->getIntRectHeight() - entity->getComponent<IntRectComponent>()->getIntRectHeight()))));
                    }
                }
            }        
        } else
            if (verifyRequiredComponent(entity)) {
                effect(entity);
            }
    }
}
void RType::HandlePatternSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    if (verifyRequiredComponent(entity)) {
        if (entity->getComponent<DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_UP) {
            entity->getComponent<DirectionPatternComponent>()->setPattern(sf::Vector2f(0, -10));
        }
        if (entity->getComponent<DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_DOWN) {
            entity->getComponent<DirectionPatternComponent>()->setPattern(sf::Vector2f(0, 10));
        }
        if (entity->getComponent<DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_LEFT) {
            entity->getComponent<DirectionPatternComponent>()->setPattern(sf::Vector2f(-10, 0));
        }
        if (entity->getComponent<DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_RIGHT) {
            entity->getComponent<DirectionPatternComponent>()->setPattern(sf::Vector2f(10, 0));
        }
        if (entity->getComponent<DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_LEFT && entity->getComponent<RType::PositionComponent>()) {
            entity->getComponent<DirectionPatternComponent>()->setPattern(sf::Vector2f(-10, 10 *(cos(entity->getComponent<RType::PositionComponent>()->getPositionX() * 0.01f))));
        }
        if (entity->getComponent<DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_RIGHT) {
            entity->getComponent<DirectionPatternComponent>()->setPattern(sf::Vector2f(10, 10 * (cos(entity->getComponent<RType::PositionComponent>()->getPositionX() * 0.01f))));
        }
    }
}

bool RType::HandlePatternSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::DirectionPatternComponent>() == nullptr) {
        return false;
    }
    return (true);
}