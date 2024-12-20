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

    std::shared_ptr<ScoreComponent> scoreComponent = nullptr;
    float difficultyCoefficient = 1;
    for (const auto &entity: entities) {
        if (entity->getComponent<EntityTypeComponent>() != nullptr && entity->getComponent<EntityTypeComponent>()->getEntityType() == E_WINDOW)
            scoreComponent = entity->getComponent<ScoreComponent>();

        if (entity->GET_DIFFICULTY != nullptr)
            difficultyCoefficient = entity->GET_DIFFICULTY->getDamageCoefficient();
        if (!verifyRequiredComponent(entity))
            continue;
        for (const auto &entity2: entities) {
            if (collides(entity, entity2)) {
                _entitiesColiding.push_back({entity, entity2});
            }
        }
    }
    handleEntityCollisions(difficultyCoefficient);
    for (const auto &entity: _entitiesToDestroy) {
        removeShieldToPlayer(entities, entity);

        if (entity->getComponent<EntityTypeComponent>() != nullptr && EntityTypeComponent::isBoss(entity->getComponent<EntityTypeComponent>()->getEntityType())) {
            for (const auto &window: entities) {
                auto level = window->getComponent<LevelComponent>();
                auto parseLevel = window->getComponent<ParseLevelInfoComponent>();
                if (level && parseLevel) {
                    if (level->getLevel() == 4)
                        return _sendMessageToAllClient(Encoder::gameEnd());
                    level->setLevel(level->getLevel() + 1);
                    parseLevel->setLevel(level->getLevel());
                    if (_sendMessageToAllClient)
                        _sendMessageToAllClient(Encoder::infoLevel(level->getLevel()));
                    break;
                }
            }
        }

        if (_sendMessageToAllClient) {
            _sendMessageToAllClient(Encoder::deleteEntity(entity->getId()));
            if (entity->getComponent<ScoreComponent>() && scoreComponent) {
                scoreComponent->setScore(scoreComponent->getScore() + entity->getComponent<ScoreComponent>()->getScore());
                _sendMessageToAllClient(Encoder::infoScore(scoreComponent->getScore()));
            }
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
        || entity->getComponent<RType::EntityTypeComponent>() == nullptr
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
    auto height1 = entity1->getComponent<IntRectComponent>()->getIntRectHeight() - entity1->getComponent<IntRectComponent>()->getIntRectTop();
    auto width2 = entity2->getComponent<IntRectComponent>()->getIntRectWidth();
    auto height2 = entity2->getComponent<IntRectComponent>()->getIntRectHeight() - entity2->getComponent<IntRectComponent>()->getIntRectTop();

    return (position1.x + (width1 * scale1.x) > position2.x
        && position1.x < position2.x + (width2 * scale2.x)
        && position1.y + (height1 * scale1.y) > position2.y
        && position1.y < position2.y + (height2 * scale2.y)
    );
}

void RType::HandleCollisionSystem::handleEntityCollision(const std::pair<std::shared_ptr<RType::Entity>, std::shared_ptr<RType::Entity>> &colidingPair, float difficultyCoefficient)
{
    const auto &entity1 = colidingPair.first;
    const auto &entity2 = colidingPair.second;
    EntityType entityType1 = GET_ENTITY_TYPE(entity1);
    EntityType entityType2 = GET_ENTITY_TYPE(entity2);

    const auto &entityDamage1 = entity1->getComponent<DamageComponent>();
    const auto &entityDamage2 = entity2->getComponent<DamageComponent>();

    if ((entityType1 == RType::E_SHIELD || entityType1 == RType::E_PLAYER) && EntityTypeComponent::isEnnemyShoot(entityType2) && entityDamage2) {
        _entitiesToDestroy.push_back(entity2);
        decreaseHealth(entity1, entityDamage2->getDamage() * difficultyCoefficient);
    } else if (entityType1 == RType::E_PLAYER && EntityTypeComponent::isMob(entityType2) && entityDamage1 && entityDamage2) {
        decreaseHealth(entity1, entityDamage2->getDamage() * difficultyCoefficient);
        decreaseHealth(entity2, entityDamage1->getDamage());
    } else if (EntityTypeComponent::isMob(entityType1) && EntityTypeComponent::isWeapon(entityType2) && entityDamage2) {
        _entitiesToDestroy.push_back(entity2);
        decreaseHealth(entity1, entityDamage2->getDamage());
    } else if (entityType1 == RType::E_PLAYER && EntityTypeComponent::isItem(entityType2)) {
        handleItemEffect(entity1, entity2);
        _entitiesToDestroy.push_back(entity2);
    }
}

void RType::HandleCollisionSystem::handleItemEffect(std::shared_ptr<RType::Entity> entity1, std::shared_ptr<RType::Entity> entity2)
{
    switch(entity2->getComponent<EntityTypeComponent>()->getEntityType()) {
        case RType::E_ITEM_WEAPON: {
            if (entity1->getComponent<RType::EntityTypeComponent>()->getWeaponType() < 3) {
                entity1->getComponent<RType::EntityTypeComponent>()->setWeaponType(RType::WeaponType(entity1->getComponent<RType::EntityTypeComponent>()->getWeaponType() + 1));
                entity1->getComponent<RType::DamageComponent>()->setDamage(entity1->getComponent<RType::DamageComponent>()->getDamage() + 1);
            }
            break;
        }
        case RType::E_ITEM_HEAL: {
            auto healthComponent = entity1->getComponent<RType::HealthComponent>();
            if (healthComponent) {
                healthComponent->setHealth(healthComponent->getHealth() + 2);
                if (healthComponent->getHealth() > healthComponent->getMaxHealth())
                    healthComponent->setHealth(healthComponent->getMaxHealth());
                if (_sendMessageToAllClient) {
                    _sendMessageToAllClient(Encoder::infoEntity(entity1->getId(), E_PLAYER,
                        entity1->GET_POSITION_X,  entity1->GET_POSITION_Y, 0, healthComponent->getHealth()));
            }
            }
            break;
        }
        case RType::E_ITEM_SHIELD: {
            auto powerUpComponent = entity1->getComponent<PowerUpComponent>();
            if (powerUpComponent && !powerUpComponent->getPowerUps(RType::SHIELD) && !powerUpComponent->getPowerUpsIsActive(RType::SHIELD)) {
                powerUpComponent->setPowerUps(RType::SHIELD, true);
                powerUpComponent->setPowerUpsIsActive(RType::SHIELD, true);
            }
            break;
        }
        case RType::E_ITEM_FORCEPOD: {
            auto powerUpComponent = entity1->getComponent<PowerUpComponent>();
            if (powerUpComponent && !powerUpComponent->getPowerUps(RType::FORCE_POD)) {
                auto entityTypeComponent = entity1->getComponent<RType::EntityTypeComponent>();
                if (entityTypeComponent && entityTypeComponent->getForcePodType() < 3) {
                    entityTypeComponent->setForcePodType(RType::ForcePodType(entityTypeComponent->getForcePodType() + 1));
                    powerUpComponent->setPowerUps(RType::FORCE_POD, true);
                }
            }
            break;
        }
        default:
            break;
    }
}

void RType::HandleCollisionSystem::handleEntityCollisions(float difficultyCoefficient)
{
    for (const auto &colidingPair: _entitiesColiding) {
        if (isInPastCollision(colidingPair))
            continue;
        handleEntityCollision(colidingPair, difficultyCoefficient);
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

    if (GET_ENTITY_TYPE(entity) == E_PLAYER) {
        if (entity->getComponent<PowerUpComponent>() && !entity->getComponent<PowerUpComponent>()->getPowerUpsIsActive(SHIELD)) {

            healthComponent->setHealth(healthComponent->getHealth() - damage);

            if (healthComponent->getHealth() <= 0)
                _entitiesToDestroy.push_back(entity);
            else if (_sendMessageToAllClient) {
                _sendMessageToAllClient(Encoder::infoEntity(entity->getId(), E_PLAYER,
                    entity->GET_POSITION_X,  entity->GET_POSITION_Y, 0, healthComponent->getHealth()));
            }
        }
    } else if (GET_ENTITY_TYPE(entity) != E_PLAYER) {

        healthComponent->setHealth(healthComponent->getHealth() - damage);

        if (healthComponent->getHealth() <= 0) {
            _entitiesToDestroy.push_back(entity);
        }
        else if (_sendMessageToAllClient && EntityTypeComponent::isBoss(GET_ENTITY_TYPE(entity))) {
                _sendMessageToAllClient(Encoder::infoEntity(entity->getId(), GET_ENTITY_TYPE(entity),
                    entity->GET_POSITION_X,  entity->GET_POSITION_Y, 0, healthComponent->getHealth()));
            }
    }
}

void RType::HandleCollisionSystem::removeShieldToPlayer(std::vector<std::shared_ptr<RType::Entity>> entities, std::shared_ptr<RType::Entity> entity)
{
    int idToFollow;

    if (entity->getComponent<DirectionPatternComponent>() == nullptr || entity->getComponent<DirectionPatternComponent>()->getEntityToFollow() == 0)
        return;
    idToFollow = entity->getComponent<DirectionPatternComponent>()->getEntityToFollow();
    if (entity->getComponent<EntityTypeComponent>() != nullptr && entity->getComponent<EntityTypeComponent>()->getEntityType() == E_SHIELD) {
        for (const auto &player: entities) {
            if (player->getComponent<EntityTypeComponent>() != nullptr && player->getComponent<EntityTypeComponent>()->getEntityType() == E_PLAYER && player->getId() == idToFollow) {
                player->getComponent<PowerUpComponent>()->setPowerUpsIsActive(RType::SHIELD, false);
                return;
            }
        }
    }
}
