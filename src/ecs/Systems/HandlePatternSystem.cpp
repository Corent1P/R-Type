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
        if (!verifyRequiredComponent(entity2)) {
            continue;;
        }
        if (entity2->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::FOLLOW_PLAYER && entity2->getComponent<RType::DirectionPatternComponent>()->getEntityToFollow() == entity->getId()) {
            entityFollowingWidth = entity2->getComponent<RType::IntRectComponent>()->getIntRectWidth();
            entityFollowingHeight = entity2->getComponent<RType::IntRectComponent>()->getIntRectHeight();
            entityFollowingScaleX = entity2->getComponent<RType::ScaleComponent>()->getScaleX();
            entityFollowingScaleY = entity2->getComponent<RType::ScaleComponent>()->getScaleY();

            entity2->getComponent<RType::DirectionPatternComponent>()->setPattern(sf::Vector2f(
                playerPositionX - (((entityFollowingWidth * entityFollowingScaleX) - (playerWidth * playerScaleX))) / 2.,
                playerPositionY - (((entityFollowingHeight * entityFollowingScaleY) - (playerHeight * playerScaleY))) / 2.
            ));
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
    if (entity->GET_PATTERN->getPatternType() == RType::NO_PATTERN)
        entity->GET_PATTERN->setPattern(sf::Vector2f(0, 0));
    if (entity->GET_PATTERN->getPatternType() == RType::STRAIGHT_UP)
        entity->GET_PATTERN->setPattern(sf::Vector2f(0, -10));
    if (entity->GET_PATTERN->getPatternType() == RType::STRAIGHT_DOWN)
        entity->GET_PATTERN->setPattern(sf::Vector2f(0, 10));
    if (entity->GET_PATTERN->getPatternType() == RType::STRAIGHT_LEFT)
        entity->GET_PATTERN->setPattern(sf::Vector2f(-10, 0));
    if (entity->GET_PATTERN->getPatternType() == RType::STRAIGHT_RIGHT)
        entity->GET_PATTERN->setPattern(sf::Vector2f(10, 0));
    if (entity->GET_PATTERN->getPatternType() == RType::UP_N_DOWN_LEFT && entity->getComponent<RType::PositionComponent>())
        entity->GET_PATTERN->setPattern(sf::Vector2f(-10, 10 *(cos(entity->getComponent<RType::PositionComponent>()->getPositionX() * 0.01f))));
    if (entity->GET_PATTERN->getPatternType() == RType::UP_N_DOWN_RIGHT)
        entity->GET_PATTERN->setPattern(sf::Vector2f(10, 10 * (cos(entity->getComponent<RType::PositionComponent>()->getPositionX() * 0.01f))));
    if (entity->GET_PATTERN->getPatternType() == RType::ZIGZAG_LEFT) {
        if (entity->getComponent<RType::PositionComponent>() == nullptr)
            return;
        if (entity->GET_PATTERN->getDirectionForZigZag() == true)
            entity->GET_PATTERN->setPattern(sf::Vector2f(-10, -10));
        else
            entity->GET_PATTERN->setPattern(sf::Vector2f(-10, 10));
        if (entity->getComponent<RType::PositionComponent>()->getPositionY() < 20)
            entity->GET_PATTERN->setDirectionForZigZag(false);
        if (entity->getComponent<RType::PositionComponent>()->getPositionY() > 1000)
            entity->GET_PATTERN->setDirectionForZigZag(true);
    }
    if (entity->GET_PATTERN->getPatternType() == RType::ZIGZAG_REVERSE_LEFT) {
        if (entity->getComponent<RType::PositionComponent>() == nullptr)
            return;
        if (entity->GET_PATTERN->getDirectionForZigZag() == true)
            entity->GET_PATTERN->setPattern(sf::Vector2f(-10, 10));
        else
            entity->GET_PATTERN->setPattern(sf::Vector2f(-10, -10));
        if (entity->getComponent<RType::PositionComponent>()->getPositionY() < 20)
            entity->GET_PATTERN->setDirectionForZigZag(true);
        if (entity->getComponent<RType::PositionComponent>()->getPositionY() > 1000)
            entity->GET_PATTERN->setDirectionForZigZag(false);
    }
    if (entity->GET_PATTERN->getPatternType() == RType::SEMI_DIAGONAL_UP) {
        entity->GET_PATTERN->setPattern(sf::Vector2f(-10, -2.5));
    }
    if (entity->GET_PATTERN->getPatternType() == RType::SEMI_DIAGONAL_DOWN) {
        entity->GET_PATTERN->setPattern(sf::Vector2f(-10, 2.5));
    }
    if (entity->GET_PATTERN->getPatternType() == RType::DIAGONAL_UP) {
        entity->GET_PATTERN->setPattern(sf::Vector2f(-10, -5));
    }
    if (entity->GET_PATTERN->getPatternType() == RType::DIAGONAL_DOWN) {
        entity->GET_PATTERN->setPattern(sf::Vector2f(-10, 5));
    }
}

bool RType::HandlePatternSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::DirectionPatternComponent>() == nullptr) {
        return false;
    }
    return (true);
}
