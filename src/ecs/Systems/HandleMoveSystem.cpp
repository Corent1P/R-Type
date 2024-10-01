/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity movements methods
*/

#include "HandleMoveSystem.hpp"

RType::HandleMoveSystem::HandleMoveSystem():
    ASystem(MOVE), _client(nullptr)
{
}

RType::HandleMoveSystem::HandleMoveSystem(std::shared_ptr<RType::Client> client):
    ASystem(MOVE), _client(client)
{
}

RType::HandleMoveSystem::~HandleMoveSystem()
{
}

void RType::HandleMoveSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    std::pair<int, int> movePosition(0, 0);
    for (const auto &entity: entities) {
        if (verifyRequiredComponent(entity)) {
            for (const auto &window: entities) {
                if (window->getComponent<RType::SFWindowComponent>() != nullptr) {
                    auto spriteBounds = entity->getComponent<RType::SpriteComponent>()->getSprite()->getGlobalBounds();
                    float windowHeight = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().y;
                    float windowWidth = window->getComponent<RType::SFWindowComponent>()->getWindow()->getSize().x;
                    if (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true && spriteBounds.left > 0) {
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(-0.1, 0);
                        movePosition.first += -100;
                    }
                    if (entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true && spriteBounds.left + spriteBounds.width < windowWidth) {
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0.1, 0);
                        movePosition.first += 100;
                    }
                    if (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) == true && spriteBounds.top > 0) {
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, -0.1);
                        movePosition.second += -100;

                    }
                    if (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == true && spriteBounds.top + spriteBounds.height < windowHeight) {
                        entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, 0.1);
                        movePosition.second += 100;
                    }
                    if (_client && (movePosition.first != 0 ||  movePosition.second != 0)) {
                        _client->send("Move " + std::to_string(movePosition.first) + " " +  std::to_string(movePosition.second));
                        // _client->send(Encoder::movePlayer(movePosition.first, movePosition.second));
                    }
                }
            }
        }
    }
}

void RType::HandleMoveSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    // if (entity->getComponent<RType::DirectionComponent>()->getDirections(LEFT) == true) {
    //     // std::cout << ">>LEFT" << std::endl;
    //     entity->getComponent<RType::SpriteComponent>()->getSprite()->move(-0.1, 0);
    // }
    // if (entity->getComponent<RType::DirectionComponent>()->getDirections(RIGHT) == true) {
    //     //  std::cout << ">>RIGHT" << std::endl;
    //     entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0.1, 0);
    // }
    // if (entity->getComponent<RType::DirectionComponent>()->getDirections(UP) == true) {
    //     //  std::cout << ">>UP" << std::endl;
    //     entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, -0.1);
    // }
    // if (entity->getComponent<RType::DirectionComponent>()->getDirections(DOWN) == true) {
    //     //  std::cout << ">>DOWN" << std::endl;
    //     entity->getComponent<RType::SpriteComponent>()->getSprite()->move(0, 0.1);
    // }
    (void) entity;
}

bool RType::HandleMoveSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::DirectionComponent>() == nullptr || entity->getComponent<RType::SpriteComponent>() == nullptr)
    {
        return false;
    }
    return (true);
}