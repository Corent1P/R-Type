/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AckMissingCommand
*/

#include "AckMissingCommand.hh"

RType::AckMissingCommand::AckMissingCommand(const COMMAND_ARGS &arguments):
    ACommand(arguments, ACK_MISSING)
{
}

void RType::AckMissingCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)client;
    (void)sendToClient;
    (void)sendToAll;
    (void)coord;
    std::cout << "ack missing commands" << std::endl;
    // TODO : implement the logic and send the lost packets to the client
}
