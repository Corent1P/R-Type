/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** handle entity shooting methods
*/

#include "HandleShootSystem.hpp"

RType::HandleShootSystem::HandleShootSystem(std::function<std::shared_ptr<Entity>()> addEntity, std::function<void(std::shared_ptr<Entity>)> deleteEntity, std::function<void(const std::basic_string<unsigned char> &message)> sendMessageToServer):
    ASystem(S_SHOOT, addEntity, deleteEntity), _sendMessageToServer(sendMessageToServer)
{
}

RType::HandleShootSystem::~HandleShootSystem()
{
}

void RType::HandleShootSystem::effects(std::vector<std::shared_ptr<RType::Entity>> entities) {
    for (const auto &entity: entities) {
        if (verifyRequiredComponent(entity)) {
            // auto playerGlobalBounds = entity->getComponent<SpriteComponent>()->getSprite()->getGlobalBounds();
            if (entity->getComponent<ActionComponent>()->getActions(RType::SHOOTING) == true) {
                entity->getComponent<RType::ActionComponent>()->setActions(RType::SHOOTING, false);

                // std::shared_ptr<RType::Entity> shotEffect = _addEntity();
                // shotEffect->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET_EFFECT));
                // std::shared_ptr<RType::PositionComponent> position = shotEffect->pushComponent(std::make_shared<RType::PositionComponent>(playerGlobalBounds.width + playerGlobalBounds.left, (playerGlobalBounds.height / 2) + playerGlobalBounds.top));
                // std::shared_ptr<RType::TextureComponent> texture = shotEffect->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/effects/flash.png"));
                // shotEffect->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 11, 19)));
                // // shotEffect->pushComponent(std::make_shared<RType::DirectionPatternComponent>(RType::STRAIGHT_RIGHT));
                // shotEffect->pushComponent(std::make_shared<RType::VelocityComponent>(7));
                // shotEffect->pushComponent(std::make_shared<RType::ClockComponent>());

                // std::shared_ptr<RType::Entity> shot = _addEntity();
                // shot->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET));
                // std::shared_ptr<RType::PositionComponent> position = shot->pushComponent(std::make_shared<RType::PositionComponent>(playerGlobalBounds.width + playerGlobalBounds.left, (playerGlobalBounds.height / 2) + playerGlobalBounds.top));
                // std::shared_ptr<RType::TextureComponent> texture = shot->pushComponent(std::make_shared<RType::TextureComponent>("./ressources/shoot-spritesheet.png"));
                // shot->pushComponent(std::make_shared<RType::SpriteComponent>(texture->getTexture(), position->getPositions(), sf::Vector2f(2, 2), sf::IntRect(0, 0, 19, 6)));
                // shot->pushComponent(std::make_shared<RType::DirectionPatternComponent>(RType::STRAIGHT_RIGHT));
                // shot->pushComponent(std::make_shared<RType::VelocityComponent>(7));
                // shot->pushComponent(std::make_shared<RType::ClockComponent>());
                // std::cout << "shoot" << std::endl;
                _sendMessageToServer(Encoder::actionPlayer(true, false, false, false));
            }
        }
        if (entity->getComponent<RType::ClockComponent>() != nullptr && entity->getComponent<RType::EntityTypeComponent>()->getEntityType() == RType::E_BULLET_EFFECT) {
            if (entity->getComponent<RType::ClockComponent>()->getClock(SHOOTING_EFFECT).getElapsedTime().asSeconds() >= 0.01) {
                _deleteEntity(entity);
            }
        }
    }
}

void RType::HandleShootSystem::effect(std::shared_ptr<RType::Entity> entity)
{
    (void) entity;
}

bool RType::HandleShootSystem::verifyRequiredComponent(std::shared_ptr<RType::Entity> entity)
{
    if (entity->getComponent<RType::DirectionComponent>() == nullptr
    || entity->getComponent<RType::ActionComponent>() == nullptr
    || entity->getComponent<RType::SpriteComponent>() == nullptr)
    {
        return false;
    }
    return (true);
}
