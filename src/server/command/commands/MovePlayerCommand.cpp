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
}

void RType::MovePlayerCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)sendToClient;
    (void)coord;
    if (!client || !client->getEntity() || !client->getEntity()->getComponent<PositionComponent>())
        return;
    std::pair<double, double> position = {client->getEntity()->getComponent<PositionComponent>()->getPositions().x, client->getEntity()->getComponent<PositionComponent>()->getPositions().y};
    position.first += ((double)_data[0]) / 10.;
    position.second += ((double)_data[1]) / 10.;
    if (position.first < 0.)
        position.first = 0.;
    if (position.first > 1920. - 52)
        position.first = 1920. - 52;
    if (position.second < 0.)
        position.second = 0.;
    if (position.second > 1080. - 79)
        position.second = 1080. - 79;
    client->getEntity()->getComponent<PositionComponent>()->setPositions(position.first, position.second);
    sendToAll(Encoder::moveEntity(client->getEntity()->getId(), position.first, position.second, 0));
}
