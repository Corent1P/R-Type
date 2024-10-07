/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MovePlayerCommand
*/

#include "MovePlayerCommand.hh"

RType::MovePlayerCommand::MovePlayerCommand(const std::vector<long> &data):
    ACommand(data, MOVE_PLAYER)
{
    std::cout << "Move command created" << std::endl;
}

void RType::MovePlayerCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll)
{
    std::cout << "execution of move command" << std::endl;
    std::pair<double, double> position = {client->getEntity()->getComponent<PositionComponent>()->getPositions().x, client->getEntity()->getComponent<PositionComponent>()->getPositions().y};
    position.first += ((double)_data[0]) / 10.;
    position.second += ((double)_data[1]) / 10.;
    if (position.first < 0.)
        position.first = 0.;
    if (position.first > 1920.)
        position.first = 1920.;
    if (position.second < 0.)
        position.second = 0.;
    if (position.second > 1080.)
        position.second = 1080.;
    client->getEntity()->getComponent<PositionComponent>()->setPositions(position.first, position.second);
    sendToAll(Encoder::moveEntity(client->getEntity()->getId(), position.first, position.second, 0));
}
