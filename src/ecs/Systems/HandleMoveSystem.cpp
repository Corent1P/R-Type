/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity movements methods
*/

#include "HandleMoveSystem.hpp"

RType::HandleMoveSystem::HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToServer, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient):
    ASystem(S_MOVE, addEntity, deleteEntity), _sendMessageToServer(sendMessageToServer), _sendMessageToAllClient(sendMessageToAllClient)
{
}

RType::HandleMoveSystem::~HandleMoveSystem()
{
}

void RType::HandleMoveSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    std::pair<int, int> movePosition(0, 0);

    for (const auto &entity: entities) {
        if (!verifyRequiredComponent(entity))
            continue;
        int speed = entity->getComponent<VelocityComponent>()->getVelocity();
        sf::Vector2 position = entity->getComponent<PositionComponent>()->getPositions();

        if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_PLAYER && !_sendMessageToAllClient) {
            if (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) != 0) {
                movePosition.first -= speed * (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) / 100.);
            }
            if (entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) != 0) {
                movePosition.first += speed *(entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) / 100.);
            }
            if (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) != 0) {
                movePosition.second -= speed * (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) / 100.);
            }
            if (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) != 0) {
                movePosition.second += speed * (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) / 100.);
            }
            entity->getComponent<RType::PositionComponent>()->setPositions(position.x + movePosition.first, position.y + movePosition.second);
        }
        if(entity->getComponent<DirectionPatternComponent>() != nullptr) {
            auto pattern = entity->getComponent<RType::DirectionPatternComponent>()->getPattern();
            if (entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == FOLLOW_PLAYER) {
                if (_sendMessageToAllClient)
                    entity->getComponent<RType::PositionComponent>()->setPositions(pattern.x, pattern.y);
            } else
                entity->getComponent<RType::PositionComponent>()->setPositions(position.x + (pattern.x * speed / 5.), position.y + (pattern.y * speed / 5.));
            if (entity->getComponent<EntityTypeComponent>()->getEntityType() != RType::E_LAYER) {
                if (DirectionPatternComponent::isPatternLeft(entity->getComponent<RType::DirectionPatternComponent>()->getPatternType())
                && entity->getComponent<RType::PositionComponent>()->getPositionX() < -300) {
                    if (_sendMessageToAllClient) {
                        _sendMessageToAllClient(Encoder::deleteEntity(entity->getId()));
                        _deleteEntity(entity);
                    }
                    continue;
                }

                if (DirectionPatternComponent::isPatternRight(entity->getComponent<RType::DirectionPatternComponent>()->getPatternType())
                && entity->getComponent<RType::PositionComponent>()->getPositionX() > 2200) {
                    if (_sendMessageToAllClient) {
                        _sendMessageToAllClient(Encoder::deleteEntity(entity->getId()));
                        _deleteEntity(entity);
                    }
                    continue;
                }

                if (EntityTypeComponent::isBoss(entity->getComponent<EntityTypeComponent>()->getEntityType())) {
                    if (entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == STRAIGHT_LEFT
                    && entity->getComponent<RType::PositionComponent>()->getPositionX() < 1920 -
                    (entity->getComponent<RType::IntRectComponent>()->getIntRectWidth() * entity->getComponent<RType::ScaleComponent>()->getScaleX())) {
                        switch (entity->getComponent<EntityTypeComponent>()->getEntityType()) {
                            case E_SPACE_SHIP_BOSS:
                                entity->getComponent<RType::DirectionPatternComponent>()->setPatternType(STRAIGHT_DOWN);
                                break;
                            default:
                                entity->getComponent<RType::DirectionPatternComponent>()->setPatternType(NO_PATTERN);
                                break;
                        }
                    }
                    if (entity->getComponent<EntityTypeComponent>()->getEntityType() == E_SPACE_SHIP_BOSS) {
                        if (entity->getComponent<RType::PositionComponent>()->getPositionY() < 0)
                            entity->getComponent<RType::DirectionPatternComponent>()->setPatternType(STRAIGHT_DOWN);
                        if (entity->getComponent<RType::PositionComponent>()->getPositionY() > 1080 -
                            (entity->getComponent<RType::IntRectComponent>()->getIntRectHeight() * entity->getComponent<RType::ScaleComponent>()->getScaleY()))
                            entity->getComponent<RType::DirectionPatternComponent>()->setPatternType(STRAIGHT_UP);
                    }

                }
            }
        }

        if (_sendMessageToServer && entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_PLAYER && (movePosition.first != 0 ||  movePosition.second != 0)) {
            _sendMessageToServer(Encoder::movePlayer(movePosition.first * 10, movePosition.second * 10));
        }

        if (_sendMessageToAllClient) {
            _sendMessageToAllClient(Encoder::moveEntity(entity->getId(), entity->getComponent<RType::PositionComponent>()->getPositionX(), entity->getComponent<RType::PositionComponent>()->getPositionY(), 0));
        }
    }
}

bool RType::HandleMoveSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<VelocityComponent>() == nullptr || (entity->getComponent<RType::DirectionComponent>() == nullptr && entity->getComponent<RType::DirectionPatternComponent>() == nullptr) || entity->getComponent<RType::PositionComponent>() == nullptr) {
        return false;
    }
    return (true);
}
