/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** GameEndCommand
*/

#include "GameEndCommand.hh"

RType::GameEndCommand::GameEndCommand(const std::vector<long> &data):
    ACommand(data, GAME_END)
{
    std::cout << "GameEnd command created" << std::endl;
}

void RType::GameEndCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll)
{
    std::cout << "execution of GameEnd command" << std::endl;
}
