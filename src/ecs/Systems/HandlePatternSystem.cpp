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

void RType::HandlePatternSystem::handlePatternFollowEntities(std::vector<std::shared_ptr<RType::Entity>> &entities, const std::shared_ptr<RType::Entity> &entity)
{
    float playerPositionX = entity->getComponent<RType::PositionComponent>()->getPositionX();
    float playerPositionY = entity->getComponent<RType::PositionComponent>()->getPositionY();
    float playerWidth = entity->getComponent<RType::IntRectComponent>()->getIntRectWidth();
    float playerHeight = entity->getComponent<RType::IntRectComponent>()->getIntRectHeight();
    float playerScaleX = entity->getComponent<RType::ScaleComponent>()->getScaleX();
    float playerScaleY = entity->getComponent<RType::ScaleComponent>()->getScaleY();

    float entityFollowingWidth;
    float entityFollowingHeight;
    float entityFollowingScaleX;
    float entityFollowingScaleY;

    for(const auto &entity2: entities) {
        if (verifyRequiredComponent(entity2)) {
            if (entity2->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::FOLLOW_PLAYER && entity2->getComponent<RType::DirectionPatternComponent>()->getEntityToFollow() == entity->getId()) {
                entityFollowingWidth = entity2->getComponent<RType::IntRectComponent>()->getIntRectWidth();
                entityFollowingHeight = entity2->getComponent<RType::IntRectComponent>()->getIntRectHeight();
                entityFollowingScaleX = entity2->getComponent<RType::ScaleComponent>()->getScaleX();
                entityFollowingScaleY = entity2->getComponent<RType::ScaleComponent>()->getScaleY();
                switch(entity2->getComponent<RType::EntityTypeComponent>()->getEntityType()) {
                    case RType::E_SHIELD:
                        entity2->getComponent<RType::DirectionPatternComponent>()->setPattern(sf::Vector2f(
                        playerPositionX - (((entityFollowingWidth * entityFollowingScaleX) - (playerWidth * playerScaleX))) / 2.,
                        playerPositionY - (((entityFollowingHeight * entityFollowingScaleY) - (playerHeight * playerScaleY))) / 2.
                        ));
                    break;
                    case RType::E_FORCEPOD:
                            entity2->getComponent<RType::DirectionPatternComponent>()->setPattern(sf::Vector2f(
                            playerPositionX - ((((entityFollowingWidth * entityFollowingScaleX) - (playerWidth * playerScaleX))) / 2.) + 20.,
                            playerPositionY - ((((entityFollowingHeight * entityFollowingScaleY) - (playerHeight * playerScaleY))) / 2.) - 40.
                            ));
                    break;
                    case RType::E_FORCEPOD_2:
                        entity2->getComponent<RType::DirectionPatternComponent>()->setPattern(sf::Vector2f(
                        playerPositionX - ((((entityFollowingWidth * entityFollowingScaleX) - (playerWidth * playerScaleX))) / 2.) + 20.,
                        playerPositionY - ((((entityFollowingHeight * entityFollowingScaleY) - (playerHeight * playerScaleY))) / 2.) + 40.
                        ));
                    break;
                    default:
                    break;
                }
                //if (entity2->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_SHIELD) {
                    // entity2->getComponent<RType::DirectionPatternComponent>()->setPattern(sf::Vector2f(
                    //     playerPositionX - (((entityFollowingWidth * entityFollowingScaleX) - (playerWidth * playerScaleX))) / 2.,
                    //     playerPositionY - (((entityFollowingHeight * entityFollowingScaleY) - (playerHeight * playerScaleY))) / 2.
                    // ));
                //}
            }
        }
    }
}

void RType::HandlePatternSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities)
{
    for (const auto &entity: entities) {
        if (entity->getComponent<EntityTypeComponent>() != nullptr && (entity->getComponent<EntityTypeComponent>()->getEntityType() == E_PLAYER || entity->getComponent<EntityTypeComponent>()->getEntityType() == E_ALLIES))
            handlePatternFollowEntities(entities, entity);
        else
            if (verifyRequiredComponent(entity))
                effect(entity);
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