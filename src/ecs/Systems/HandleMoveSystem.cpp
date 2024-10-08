/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity movements methods
*/

#include "HandleMoveSystem.hpp"

RType::HandleMoveSystem::HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity):
    ASystem(S_MOVE, addEntity, deleteEntity), _client(nullptr), _sendMessageToAllClient(nullptr)
{
}

RType::HandleMoveSystem::HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToAllClient):
    ASystem(S_MOVE, addEntity, deleteEntity), _client(nullptr), _sendMessageToAllClient(sendMessageToAllClient)
{
}

RType::HandleMoveSystem::HandleMoveSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::shared_ptr<RType::Client> client):
    ASystem(S_MOVE, addEntity, deleteEntity), _client(client), _sendMessageToAllClient(nullptr)
{
}

RType::HandleMoveSystem::~HandleMoveSystem()
{
}

void RType::HandleMoveSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    std::pair<int, int> movePosition(0, 0);

    for (const auto &entity: entities) {
        if (verifyRequiredComponent(entity)) {
            int speed = entity->getComponent<VelocityComponent>()->getVelocity();;
            sf::Vector2 position = entity->getComponent<PositionComponent>()->getPositions();

            if (entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_PLAYER) {
                if (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true) {
                    movePosition.first -= speed;
                }
                if (entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true) {
                    movePosition.first += speed;
                }
                if (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) == true) {
                    movePosition.second -= speed;
                }
                if (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == true) {
                    movePosition.second += speed;
                }
                entity->getComponent<RType::PositionComponent>()->setPositions(position.x + movePosition.first, position.y + movePosition.second);
            }
            if(entity->getComponent<DirectionPatternComponent>() != nullptr) {
                auto pattern = entity->getComponent<RType::DirectionPatternComponent>()->getPattern();
                entity->getComponent<RType::PositionComponent>()->setPositions(position.x + (pattern.x * speed / 5.), position.y + (pattern.y * speed / 5.));
                if (entity->getComponent<EntityTypeComponent>()->getEntityType() != RType::E_LAYER) {
                    if ((entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_LEFT
                    || entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_LEFT)
                    && entity->getComponent<RType::PositionComponent>()->getPositionX() < -300) {
                        if (_sendMessageToAllClient) {
                            _sendMessageToAllClient(Encoder::deleteEntity(entity->getId()));
                            _deleteEntity(entity);
                        }
                        continue;
                    }

                    if ((entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::STRAIGHT_RIGHT
                    || entity->getComponent<RType::DirectionPatternComponent>()->getPatternType() == RType::UP_N_DOWN_RIGHT)
                    && entity->getComponent<RType::PositionComponent>()->getPositionX() > 2200) {
                        if (_sendMessageToAllClient) {
                            _sendMessageToAllClient(Encoder::deleteEntity(entity->getId()));
                            _deleteEntity(entity);
                        }
                        continue;
                    }
                }
            }

            if (_client && entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == E_PLAYER && (movePosition.first != 0 ||  movePosition.second != 0)) {
                _client->send(Encoder::movePlayer(movePosition.first * 10, movePosition.second * 10));
            }

            if (_sendMessageToAllClient) {
                _sendMessageToAllClient(Encoder::moveEntity(entity->getId(), entity->getComponent<RType::PositionComponent>()->getPositionX(), entity->getComponent<RType::PositionComponent>()->getPositionY(), 0));
            }
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