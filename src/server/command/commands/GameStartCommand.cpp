/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameStartCommand
*/

#include "GameStartCommand.hh"

RType::GameStartCommand::GameStartCommand(const std::vector<long> &data):
    ACommand(data, GAME_START)
{
    std::cout << "GameStart command created" << std::endl;
}

void RType::GameStartCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)client;
    (void)sendToClient;
    (void)sendToAll;
    (void)coord;
    std::cout << "execution of GameStart command" << std::endl;
}
