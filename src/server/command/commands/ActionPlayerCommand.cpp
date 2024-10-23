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

    float x = client->getEntity()->getComponent<PositionComponent>()->getPositions().x + (client->getEntity()->getComponent<IntRectComponent>()->getIntRectWidth() * client->getEntity()->getComponent<ScaleComponent>()->getScaleX());
    float y = client->getEntity()->getComponent<PositionComponent>()->getPositions().y + ((client->getEntity()->getComponent<IntRectComponent>()->getIntRectHeight() * client->getEntity()->getComponent<ScaleComponent>()->getScaleY()) / 2.);

    std::shared_ptr<RType::PositionComponent> position = bullet->pushComponent(std::make_shared<RType::PositionComponent>(x, y));
    bullet->pushComponent(std::make_shared<RType::DirectionPatternComponent>(RType::STRAIGHT_RIGHT));
    bullet->pushComponent(std::make_shared<RType::VelocityComponent>(21));
    bullet->pushComponent(std::make_shared<RType::ClockComponent>());
    bullet->pushComponent(std::make_shared<RType::DamageComponent>(client->getEntity()->getComponent<DamageComponent>()->getDamage()));
    std::cout << "bullet damage:" << bullet->getComponent<DamageComponent>()->getDamage() <<std::endl;
    bullet->pushComponent(std::make_shared<RType::MenuComponent>(GAME));

    switch (client->getEntity()->getComponent<RType::EntityTypeComponent>()->getWeaponType()) {
        case RType::LVL_1:
            bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET));
            bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 19, 6));
            bullet->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
            sendToAll(Encoder::newEntity(E_BULLET, bullet->getId(), position->getPositionX(), position->getPositionY()));
            break;
        case RType::LVL_2:
            bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET_2));
            bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 228, 192));
            bullet->pushComponent(std::make_shared<RType::ScaleComponent>(0.5, 0.5));
            sendToAll(Encoder::newEntity(E_BULLET_2, bullet->getId(), position->getPositionX(), position->getPositionY()));
            break;
        case RType::LVL_3:
            bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET_3));
            bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 32, 32));
            bullet->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
            sendToAll(Encoder::newEntity(E_BULLET_3, bullet->getId(), position->getPositionX(), position->getPositionY()));
            break;
        case RType::LVL_4:
            bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET_4));
            bullet->pushComponent(std::make_shared<RType::IntRectComponent>(0, 0, 63, 32));
            bullet->pushComponent(std::make_shared<RType::ScaleComponent>(2.0, 2.0));
            sendToAll(Encoder::newEntity(E_BULLET_4, bullet->getId(), position->getPositionX(), position->getPositionY()));
            break;
        default:
            break;
    }
}
