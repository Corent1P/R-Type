/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MoveEntityCommand
*/

#include "MoveEntityCommand.hh"

RType::MoveEntityCommand::MoveEntityCommand(const COMMAND_ARGS &arguments):
    ACommand(arguments, MOVE_ENTITY)
{
}

void RType::MoveEntityCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)client;
    (void)sendToClient;
    (void)sendToAll;
    (void)coord;
}
