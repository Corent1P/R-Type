/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ActionPlayerCommand
*/

#include "ActionPlayerCommand.hh"

RType::ActionPlayerCommand::ActionPlayerCommand(const std::vector<long> &data):
    ACommand(data, ACTION_PLAYER)
{
}

void RType::ActionPlayerCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)sendToClient;
    std::shared_ptr<RType::Entity> bullet = coord.generateNewEntity();

    if (client == nullptr || client->getEntity() == nullptr
    || client->getEntity()->getComponent<PositionComponent>() == nullptr
    || client->getEntity()->getComponent<ScaleComponent>() == nullptr
    || client->getEntity()->getComponent<IntRectComponent>() == nullptr
    || client->getEntity()->getComponent<DamageComponent>() == nullptr
    || client->getEntity()->getComponent<EntityTypeComponent>() == nullptr) {
        return;
    }

    sf::Vector2f position = getBulletPosition(client);

    bullet->pushComponent(std::make_shared<RType::PositionComponent>(position.x, position.y));
    bullet->pushComponent(std::make_shared<RType::DirectionPatternComponent>(RType::STRAIGHT_RIGHT));
    bullet->pushComponent(std::make_shared<RType::VelocityComponent>(21));
    bullet->pushComponent(std::make_shared<RType::ClockComponent>());
    bullet->pushComponent(std::make_shared<RType::DamageComponent>(client->getEntity()->getComponent<DamageComponent>()->getDamage()));
    bullet->pushComponent(std::make_shared<RType::MenuComponent>(GAME));

    switch (client->getEntity()->getComponent<RType::EntityTypeComponent>()->getWeaponType()) {
        case RType::LVL_1:
            bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET));
            bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 19, 6));
            bullet->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
            sendToAll(Encoder::newEntity(E_BULLET, bullet->getId(), position.x, position.y));
            break;
        case RType::LVL_2:
            bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET_2));
            bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 228, 192));
            bullet->pushComponent(std::make_shared<RType::ScaleComponent>(0.5, 0.5));
            sendToAll(Encoder::newEntity(E_BULLET_2, bullet->getId(), position.x, position.y));
            break;
        case RType::LVL_3:
            bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET_3));
            bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 32, 32));
            bullet->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
            sendToAll(Encoder::newEntity(E_BULLET_3, bullet->getId(), position.x, position.y));
            break;
        case RType::LVL_4:
            bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET_4));
            bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 63, 32));
            bullet->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
            sendToAll(Encoder::newEntity(E_BULLET_4, bullet->getId(), position.x, position.y));
            break;
        default:
            break;
    }
}

sf::Vector2f RType::ActionPlayerCommand::getBulletPosition(std::shared_ptr<ClientServer> client)
{
    std::shared_ptr<RType::Entity> entity = client->getEntity();
    
    sf::Vector2f position = entity->getComponent<PositionComponent>()->getPositions();
    sf::Vector2f scale = entity->getComponent<ScaleComponent>()->getScales();
    sf::Vector2f bulletPosition;
    WeaponType weaponType = entity->getComponent<EntityTypeComponent>()->getWeaponType();
    sf::Vector2f bulletSize = getBulletSize(weaponType);

    bulletPosition.x = position.x + (entity->getComponent<IntRectComponent>()->getIntRectWidth() * scale.x);
    bulletPosition.y = position.y + ((entity->getComponent<IntRectComponent>()->getIntRectHeight() * scale.y) / 2) - bulletSize.y / 2;
    return bulletPosition;
}

sf::Vector2f RType::ActionPlayerCommand::getBulletSize(WeaponType weaponType)
{
    sf::Vector2f bulletSize;

    switch (weaponType) {
        case RType::LVL_1:
            bulletSize.x = 19 * 2.;
            bulletSize.y = 6 * 2.;
            break;
        case RType::LVL_2:
            bulletSize.x = 228 * 0.5;
            bulletSize.y = 192 * 0.5;
            break;
        case RType::LVL_3:
            bulletSize.x = 32 * 2.;
            bulletSize.y = 32 * 2.;
            break;
        case RType::LVL_4:
            bulletSize.x = 63 * 2.;
            bulletSize.y = 32 * 2.;
            break;
        default:
            break;
    }
    return bulletSize;
}
