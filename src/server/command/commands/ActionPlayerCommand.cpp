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
    std::cout << "Action command created" << std::endl;
}

void RType::ActionPlayerCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    std::shared_ptr<RType::Entity> bullet = coord.generateNewEntity();

    bullet->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::E_BULLET));
    std::shared_ptr<RType::PositionComponent> position = bullet->pushComponent(std::make_shared<RType::PositionComponent>(client->getEntity()->getComponent<PositionComponent>()->getPositions().x, client->getEntity()->getComponent<PositionComponent>()->getPositions().y));
    bullet->pushComponent(std::make_shared<RType::DirectionPatternComponent>(RType::STRAIGHT_RIGHT));
    bullet->pushComponent(std::make_shared<RType::VelocityComponent>(21));
    bullet->pushComponent(std::make_shared<RType::ClockComponent>());

    std::cout << "ActionPlayerCommand " << bullet->getId() << std::endl;

    sendToAll(Encoder::newEntity(E_BULLET, bullet->getId(), position->getPositionX(), position->getPositionY()));
}
