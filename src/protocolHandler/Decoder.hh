/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Decoder
*/


#pragma once

#include "Encoder.hh"
#include <utility>
#include <vector>

#define COMMAND_ARGS std::vector<long>

/*
* @brief Define the header of the packet,
* the first parameter is the type of the packet and
* the second is the number of the packet
*/
#define HEADER std::pair<RType::PacketType, std::uint8_t>
#define PACKET std::pair<HEADER, COMMAND_ARGS>

namespace RType {

    /**
    * @brief Class to decode the data received from the client and the server
    */
    class Decoder {
    public:
        /**
        * @brief Decode the connexion packet
        * INFO: please use this method to decode any packet
        *
        * @param packet Packet received
        *
        * @return return the command info composed of two parts : the type of the command and the arguments of the command
        */
        static PACKET getCommandInfo(U_STRING &packet);

        /**
        * @brief Decode the header of the packet to get the type of packet received
        *
        * @param packet Packet received
        *
        * @return PacketType Type of the packet
        */
        static PacketType getType(U_STRING &packet);

        /**
        * @brief Decode the header of the packet to get the size of the packet received
        *
        * @param packet Packet received
        *
        * @return std::size_t Size of the packet
        */
        static std::size_t getSize(U_STRING &packet);

        /**
        * @brief Decode the header of the packet to get the number of the packet received
        *
        * @param packet Packet received
        *
        * @return std::uint8_t Number of the packet
        */
        static std::uint8_t getPacketNumber(U_STRING &packet);

        /**
        * @brief Decrypt the header of the packet
        *
        * @param packet Packet received
        *
        * @return HEADER the content of the header
        */
        static HEADER decryptHeader(U_STRING &packet);

        /**
        * @brief Decode the new entity packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS newEntity(U_STRING &packet);

        /**
        * @brief Decode the delete entity packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS deleteEntity(U_STRING &packet);

        /**
        * @brief Decode the move entity packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS moveEntity(U_STRING &packet);

        /**
        * @brief Decode the info level packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS infoLevel(U_STRING &packet);

        /**
        * @brief Decode the info entity packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS infoEntity(U_STRING &packet);

        /**
        * @brief Decode the move player packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS movePlayer(U_STRING &packet);

        /**
        * @brief Decode the action player packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS actionPlayer(U_STRING &packet);

        /**
        * @brief Decode the game start packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS gameStart(U_STRING &packet);

        /**
        * @brief Decode the game end packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS gameEnd(U_STRING &packet);

        /**
        * @brief Decode the game over packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS error(U_STRING &packet);
    };
}
