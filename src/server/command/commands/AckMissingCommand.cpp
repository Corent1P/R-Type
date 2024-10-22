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

bool RType::AckMissingCommand::inVector(const std::vector<int32_t> &tab, u_int8_t value)
{
    for (std::size_t i = 0; i < tab.size(); i++)
        if (tab[i] == value)
            return true;
    return false;
}

void RType::AckMissingCommand::execute(std::shared_ptr<ClientServer> client, FUNCTION_SEND sendToClient, FUNCTION_SEND sendToAll, Coordinator &coord)
{
    (void)sendToAll;
    (void)coord;
    std::vector<U_STRING> packetsSent = client->getPacketsSent();
    // int clientId = client->getEntity()->getId();

    // std::cout << "client " << clientId << " nack command informations :" << std::endl;
    // std::cout << "packet sents = [";
    // for (std::size_t i = 0; i < packetsSent.size(); i++)
    //     std::cout << (int)Decoder::getPacketNumber(packetsSent[i]) << ", ";
    // std::cout << "]" << std::endl;

    // std::cout << "packet clients received = [";
    // for (std::size_t i = 0; i < _data.size(); i++)
    //     std::cout << _data[i] << ", ";
    // std::cout << "]" << std::endl;

    for (std::size_t i = 0; i < packetsSent.size(); i++)
        if (!inVector(_data, Decoder::getPacketNumber(packetsSent[i])))
            sendToClient(packetsSent[i]);
    client->resetPacketsSent();
}

int RType::AckMissingCommand::getIndexLostPacketWithId(std::vector<U_STRING> &sentPackets, u_int8_t packetId)
{
    for (std::size_t i = 0; i < sentPackets.size(); i++)
        if (Decoder::getPacketNumber(sentPackets[i]) == packetId)
            return i;
    return -1;
}
