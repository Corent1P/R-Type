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
    (void)sendToAll;
    (void)coord;
    std::array<U_STRING, MAX_PACKETS> packetsSent = client->getPacketsSent();
    int indexLostCommand;

    std::cout << "ack command:" << std::endl;
    for (std::size_t i = 0; i < _data.size(); i++) {
        if (_data[i] == 0) {
            indexLostCommand = getIndexLostPacketWithId(packetsSent, _data[i]);
            std::cout << "indexLostCommand = " << indexLostCommand << std::endl;
            if (indexLostCommand != -1)
                sendToClient(packetsSent[indexLostCommand]);
        }
    }
    client->resetPacketsSent();
}

int RType::AckMissingCommand::getIndexLostPacketWithId(std::array<U_STRING, MAX_PACKETS> &sentPackets, u_int8_t packetId)
{
    for (int i = 0; i < MAX_PACKETS; i++)
        if (Decoder::getPacketNumber(sentPackets[i]) == packetId)
            return i;
    return -1;
}
