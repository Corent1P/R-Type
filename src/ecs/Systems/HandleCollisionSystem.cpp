/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity Collision methods
*/

#include "HandleCollisionSystem.hpp"

RType::HandleCollisionSystem::HandleCollisionSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_COLISION, addEntity, deleteEntity), _sendMessageToAllClient(nullptr)
{
}

RType::HandleCollisionSystem::HandleCollisionSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient):
    ASystem(S_COLISION, addEntity, deleteEntity), _sendMessageToAllClient(sendMessageToAllClient)
{
}

RType::HandleCollisionSystem::~HandleCollisionSystem()
{
}

void RType::HandleCollisionSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
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
    handleEntityCollisions();
    for (const auto &entity: _entitiesToDestroy) {
        if (_sendMessageToAllClient) {
            _sendMessageToAllClient(Encoder::deleteEntity(entity->getId()));
            _deleteEntity(entity);
        }
    }
}

void RType::HandleCollisionSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
}

bool RType::HandleCollisionSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::PositionComponent>() == nullptr
        || entity->getComponent<RType::IntRectComponent>() == nullptr
        || entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_LAYER) {
        return false;
    }
    return (true);
}

bool RType::HandleCollisionSystem::collides(std::shared_ptr<RType::Entity> entity1, std::shared_ptr<RType::Entity> entity2)
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

void RType::HandleCollisionSystem::handleEntityCollision(const std::pair<std::shared_ptr<RType::Entity>, std::shared_ptr<RType::Entity>> &colidingPair)
{
    const auto &entity1 = colidingPair.first;
    const auto &entity2 = colidingPair.second;
    EntityType entityType1 = GET_ENTITY_TYPE(entity1);
    EntityType entityType2 = GET_ENTITY_TYPE(entity2);

    if (entityType1 == RType::E_PLAYER && entityType2 == RType::E_ENNEMY_BULLET) {
        _entitiesToDestroy.push_back(entity2);
        decreaseHealth(entity1, 1);
    } else if (entityType1 == RType::E_PLAYER && EntityTypeComponent::isMob(entityType2)) {
        decreaseHealth(entity1, 1);
        decreaseHealth(entity2, 1);
    } else if (EntityTypeComponent::isMob(entityType1) && entityType2 == RType::E_BULLET) {
        _entitiesToDestroy.push_back(entity2);
        decreaseHealth(entity1, 1);

    }
}

void RType::HandleCollisionSystem::handleEntityCollisions(void)
{
    for (const auto &colidingPair: _entitiesColiding) {
        if (isInPastCollision(colidingPair))
            continue;
        handleEntityCollision(colidingPair);
    }
}

bool RType::HandleCollisionSystem::isInPastCollision(const std::pair<std::shared_ptr<RType::Entity>, std::shared_ptr<RType::Entity>> &colidingPair)
{
    for (const auto &colidingPairBefore: _entitiesColidingBefore) {
        if (colidingPair == colidingPairBefore)
            return true;
    }
    return false;
}

void RType::HandleCollisionSystem::decreaseHealth(std::shared_ptr<RType::Entity> entity, int damage)
{
    auto healthComponent = entity->getComponent<HealthComponent>();
    healthComponent->setHealth(healthComponent->getHealth() - damage);
    if (healthComponent->getHealth() <= 0)
        _entitiesToDestroy.push_back(entity);
    else if (healthComponent->getHealth() > 0 && _sendMessageToAllClient && GET_ENTITY_TYPE(entity) == E_PLAYER) {
        std::cout << "health: " << healthComponent->getHealth() << std::endl;
        _sendMessageToAllClient(Encoder::infoEntity(entity->getId(), E_PLAYER,
            entity->GET_POSITION_X,  entity->GET_POSITION_Y, 0, healthComponent->getHealth()));
    }
}
