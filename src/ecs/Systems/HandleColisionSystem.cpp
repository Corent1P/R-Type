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
    _entitiesToDestroy.clear();
    _entitiesColidingBefore = _entitiesColiding;
    _entitiesColiding.clear();
    for (const auto &entity: entities) {
        if (!verifyRequiredComponent(entity))
            continue;
        for (const auto &entity2: entities) {
            if (collides(entity, entity2)) {
                _entitiesColiding.push_back({entity, entity2});
            }
        }
    }
    handleEntityColisions();
    for (const auto &entity: _entitiesToDestroy) {
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

bool RType::HandleColisionSystem::collides(std::shared_ptr<RType::Entity> entity1, std::shared_ptr<RType::Entity> entity2)
{
    if (entity1->getId() == entity2->getId())
        return false;
    if (!verifyRequiredComponent(entity2))
        return false;
    auto position1 = entity1->getComponent<PositionComponent>()->getPositions();
    auto position2 = entity2->getComponent<PositionComponent>()->getPositions();
    sf::Vector2f scale1 = (entity1->getComponent<ScaleComponent>()) ? entity1->getComponent<ScaleComponent>()->getScales() : sf::Vector2f{1.0, 1.0};
    sf::Vector2f scale2 = (entity2->getComponent<ScaleComponent>()) ? entity2->getComponent<ScaleComponent>()->getScales() : sf::Vector2f{1.0, 1.0};
    auto width1 = entity1->getComponent<IntRectComponent>()->getIntRectWidth();
    auto height1 = entity1->getComponent<IntRectComponent>()->getIntRectHeight();
    auto width2 = entity2->getComponent<IntRectComponent>()->getIntRectWidth();
    auto height2 = entity2->getComponent<IntRectComponent>()->getIntRectHeight();

    return (position1.x + (width1 * scale1.x) > position2.x
        && position1.x < position2.x + (width2 * scale2.x)
        && position1.y + (height1 * scale2.y) > position2.y
        && position1.y < position2.y + (height2 * scale2.y)
    );
}

void RType::HandleColisionSystem::handleEntityColision(const std::pair<std::shared_ptr<RType::Entity>, std::shared_ptr<RType::Entity>> &colidingPair)
{
    const auto &entity1 = colidingPair.first;
    const auto &entity2 = colidingPair.second;
    EntityType entityType1 = GET_ENTITY_TYPE(entity1);
    EntityType entityType2 = GET_ENTITY_TYPE(entity2);

    if (entityType1 == RType::E_PLAYER && entityType2 == RType::E_BULLET)
        std::cout << "Player intersect bullet" << std::endl;
    if (entityType1 == RType::E_BULLET && entityType2 == RType::E_PLAYER)
        std::cout << "Bullet intersect player" << std::endl;
    if (entityType1 == RType::E_PLAYER && EntityTypeComponent::isMob(entityType2))
        std::cout << "Player intersect mob" << std::endl;
    if (EntityTypeComponent::isMob(entityType1) && entityType2 == RType::E_PLAYER)
        std::cout << "Mob intersect Player" << std::endl;
    if (entityType1 == RType::E_BULLET && EntityTypeComponent::isMob(entityType2)) {
        _entitiesToDestroy.push_back(entity1);
        entity2->getComponent<HealthComponent>()->setHealth(entity2->getComponent<HealthComponent>()->getHealth() - 1);
        if (entity2->getComponent<HealthComponent>()->getHealth() <= 0)
            _entitiesToDestroy.push_back(entity2);
        std::cout << "Bullet intersect mob" << std::endl;
    }
    if (entityType1 == RType::E_PLAYER && entityType2 == RType::E_ITEM) {
        _entitiesToDestroy.push_back(entity2);
        std::cout << "Item intersect player" << std::endl;
    }
    if (EntityTypeComponent::isMob(entityType1) && entityType2 == RType::E_BULLET) {
        std::cout << "Mob intersect Bullet" << std::endl;
    }
}

void RType::HandleColisionSystem::handleEntityColisions(void)
{
    for (const auto &colidingPair: _entitiesColiding) {
        if (isInPastColision(colidingPair))
            continue;
        handleEntityColision(colidingPair);
    }
}

bool RType::HandleColisionSystem::isInPastColision(const std::pair<std::shared_ptr<RType::Entity>, std::shared_ptr<RType::Entity>> &colidingPair)
{
    for (const auto &colidingPairBefore: _entitiesColidingBefore) {
        if (colidingPair == colidingPairBefore)
            return true;
    }
    return false;
}
