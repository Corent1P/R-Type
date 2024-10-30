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
#define COMMAND_INFO std::pair<RType::PacketType, COMMAND_ARGS>

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
        static COMMAND_INFO getCommandInfo(U_STRING &packet);

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
        * @brief Decode the info score packet
        *
        * @param packet Packet received
        *
        * @return COMMAND_ARGS the content of the command
        */
        static COMMAND_ARGS infoScore(U_STRING &packet);


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
    };
}
