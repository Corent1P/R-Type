/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity Colision methods
*/

#include "HandleColisionSystem.hpp"

RType::HandleColisionSystem::HandleColisionSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_COLISION, addEntity, deleteEntity), _sendMessageToAllClient(nullptr)
{
}

RType::HandleColisionSystem::HandleColisionSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient):
    ASystem(S_COLISION, addEntity, deleteEntity), _sendMessageToAllClient(sendMessageToAllClient)
{
}

RType::HandleColisionSystem::~HandleColisionSystem()
{
}

void RType::HandleColisionSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    std::vector<std::shared_ptr<RType::Entity>> entitiesToDestroy;
    for (const auto &entity: entities) {
        if (verifyRequiredComponent(entity)) {
            auto position1 = entity->getComponent<PositionComponent>()->getPositions();
            sf::Vector2f scale1({1.0, 1.0});
            if (entity->getComponent<ScaleComponent>())
                scale1 = entity->getComponent<ScaleComponent>()->getScales();
            auto width1 = entity->getComponent<IntRectComponent>()->getIntRectWidth();
            auto height1 = entity->getComponent<IntRectComponent>()->getIntRectWidth();
            for (const auto &otherEntity: entities) {
                if (entity->getId() != otherEntity->getId() && verifyRequiredComponent(otherEntity)) {
                    sf::Vector2f scale2({1.0, 1.0});
                    if (otherEntity->getComponent<ScaleComponent>())
                        scale2 = otherEntity->getComponent<ScaleComponent>()->getScales();
                    auto position2 = otherEntity->getComponent<PositionComponent>()->getPositions();
                    auto width2 = otherEntity->getComponent<IntRectComponent>()->getIntRectWidth();
                    auto height2 = otherEntity->getComponent<IntRectComponent>()->getIntRectWidth();
                    if (position1.x + (width1 * scale1.x) > position2.x
                    && position1.x < position2.x + (width2 * scale2.x)
                    && position1.y + (height1 * scale2.y) > position2.y
                    && position1.y < position2.y + (height2 * scale2.y)) {
                        if (GET_ENTITY_TYPE(entity) == RType::E_PLAYER && GET_ENTITY_TYPE(otherEntity) == RType::E_BULLET)
                            std::cout << "Player intersect bullet" << std::endl;
                        if (GET_ENTITY_TYPE(entity) == RType::E_BULLET && GET_ENTITY_TYPE(otherEntity) == RType::E_PLAYER)
                            std::cout << "Bullet intersect player" << std::endl;
                        if (GET_ENTITY_TYPE(entity) == RType::E_PLAYER && GET_ENTITY_TYPE(otherEntity) == RType::E_MOB)
                            std::cout << "Player intersect mob" << std::endl;
                        if (GET_ENTITY_TYPE(entity) == RType::E_MOB && GET_ENTITY_TYPE(otherEntity) == RType::E_PLAYER)
                            std::cout << "Mob intersect Player" << std::endl;
                        if (GET_ENTITY_TYPE(entity) == RType::E_BULLET && GET_ENTITY_TYPE(otherEntity) == RType::E_MOB) {
                            entitiesToDestroy.push_back(entity);
                            entitiesToDestroy.push_back(otherEntity);
                            std::cout << "Bullet intersect mob" << std::endl;
                        }
                        if (GET_ENTITY_TYPE(entity) == RType::E_MOB && GET_ENTITY_TYPE(otherEntity) == RType::E_BULLET) {
                            std::cout << "Mob intersect Bullet" << std::endl;
                        }
                    }
                }
            }
        }
    }
    for (const auto &entity: entitiesToDestroy) {
        if (_sendMessageToAllClient) {
            _sendMessageToAllClient(Encoder::deleteEntity(entity->getId()));
            _deleteEntity(entity);
        }
    }
}

void RType::HandleColisionSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
}

bool RType::HandleColisionSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr
    || entity->getComponent<RType::IntRectComponent>() == nullptr
    || entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_LAYER) {
        return false;
    }
    return (true);
}
