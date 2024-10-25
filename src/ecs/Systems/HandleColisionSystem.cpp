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
        if (entity->getComponent<EntityTypeComponent>() != nullptr && entity->getComponent<EntityTypeComponent>()->getEntityType() == E_SHIELD) {
            std::cout << "Shield in destroy vector" << std::endl;
            for (const auto &player: entities) {
                if (player->getComponent<EntityTypeComponent>() != nullptr && player->getComponent<EntityTypeComponent>()->getEntityType() == E_PLAYER) {
                    player->getComponent<PowerUpComponent>()->setPowerUpsIsActive(RType::SHIELD, false);
                }
            }
        }
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
        && position1.y + (height1 * scale1.y) > position2.y
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
    if (EntityTypeComponent::isWeapon(entityType1) && EntityTypeComponent::isMob(entityType2)) {
        entity2->getComponent<HealthComponent>()->setHealth(entity2->getComponent<HealthComponent>()->getHealth() - entity1->getComponent<DamageComponent>()->getDamage());
        if (entity2->getComponent<HealthComponent>()->getHealth() <= 0)
            _entitiesToDestroy.push_back(entity2);
        _entitiesToDestroy.push_back(entity1);
        std::cout << "Bullet intersect mob" << std::endl;
    }
    if (entityType1 == RType::E_PLAYER && EntityTypeComponent::isItem(entityType2)) {
        std::cout << "Item intersect player" << std::endl;
        handleItemEffect(entity1, entity2);
        _entitiesToDestroy.push_back(entity2);
    }
    if (entityType1 == RType::E_SHIELD && EntityTypeComponent::isMob(entityType2)) {
        entity1->getComponent<HealthComponent>()->setHealth(entity1->getComponent<HealthComponent>()->getHealth() - entity2->getComponent<DamageComponent>()->getDamage());
        std::cout << "Mob intersect Shield hp: "<< entity1->getComponent<HealthComponent>()->getHealth() << std::endl;
        if (entity1->getComponent<HealthComponent>()->getHealth() <= 0) {
            std::cout << "Shield need to be destroyed" << std::endl;
            _entitiesToDestroy.push_back(entity1);
        }
    }
    if (EntityTypeComponent::isMob(entityType1) && entityType2 == RType::E_BULLET) {
        std::cout << "Mob intersect Bullet" << std::endl;
    }
}

void RType::HandleColisionSystem::handleItemEffect(std::shared_ptr<RType::Entity> entity1, std::shared_ptr<RType::Entity> entity2)
{
    switch(entity2->getComponent<EntityTypeComponent>()->getEntityType())
    {
        case RType::E_ITEM_WEAPON:
            if (entity1->getComponent<RType::EntityTypeComponent>()->getWeaponType() < 3) {
                entity1->getComponent<RType::EntityTypeComponent>()->setWeaponType(RType::WeaponType(entity1->getComponent<RType::EntityTypeComponent>()->getWeaponType() + 1));
                entity1->getComponent<RType::DamageComponent>()->setDamage(entity1->getComponent<RType::DamageComponent>()->getDamage() + 1);
            }
            break;
        case RType::E_ITEM_HEAL:
            std::cout << "player health + 1" << std::endl;
            entity1->getComponent<RType::HealthComponent>()->setHealth(entity1->getComponent<RType::HealthComponent>()->getHealth() + 1);
            break;
        case RType::E_ITEM_SHIELD:
            if (entity1->getComponent<PowerUpComponent>() != nullptr && entity1->getComponent<PowerUpComponent>()->getPowerUps(RType::SHIELD) == false) {
                if (entity1->getComponent<PowerUpComponent>()->getPowerUpsIsActive(RType::SHIELD) == false) {
                    entity1->getComponent<PowerUpComponent>()->setPowerUps(RType::SHIELD, true);
                    entity1->getComponent<PowerUpComponent>()->setPowerUpsIsActive(RType::SHIELD, true);
                }
            }
            break;

        default:
        break;
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
