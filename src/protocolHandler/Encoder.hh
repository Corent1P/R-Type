/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Encoder
*/

#pragma once

#include <bitset>
#include <cstdint>
#include <iostream>
#include <stdbool.h>
#include <vector>
#include <array>

#define U_STRING std::basic_string<unsigned char>
#define PACKET_PER_TICK 64

namespace RType {

    /**
    * @brief Enum to define the type of the packet
    */
    enum PacketType {
        UNKNOWN = -1,
        CONNEXION = 0,
        DISCONNEXION = 1,
        CONNEXION_CONFIRM = 2,
        ACK_MISSING = 3,
        GAME_START = 4,
        GAME_END = 5,
        INFO_LEVEL = 6,
        NEW_ENTITY = 7,
        DELETE_ENTITY = 8,
        MOVE_ENTITY = 9,
        INFO_ENTITY = 10,
        MOVE_PLAYER = 11,
        ACTION_PLAYER = 12,
        ERROR = 13,
    };

    /**
    * @brief Class to encode the data to communicate with the client and the server
    */
    class Encoder {
    public:
        /**
        * @brief Encode the header of the packet
        *
        * @param packetNumber The number of the packet
        * @param size Total size of the packet, excluding the header
        * @param type Type of the packet
        *
        * @return U_STRING Encoded header
        */
        static U_STRING header(std::uint8_t packetNumber, std::uint16_t size, unsigned char type);

        /**
        * @brief Encode the connexion packet
        *
        * @param packetNumber The number of the packet
        *
        * @return U_STRING Encoded connexion packet
        */
        static U_STRING connexion(std::uint8_t packetNumber);

        /**
        * @brief Encode the disconnexion packet
        *
        * @param packetNumber The number of the packet
        *
        * @return U_STRING Encoded disconnexion packet
        */
        static U_STRING disconnexion(std::uint8_t packetNumber);

        /**
        * @brief Encode the new entity packet
        *
        * @param packetNumber The number of the packet
        * @param type Type of the entity
        * @param id The unique id of the entity
        * @param x The x position of the entity
        * @param y The y position of the entity
        *
        * @return U_STRING Encoded new entity packet
        */
        static U_STRING newEntity(std::uint8_t packetNumber,
                                  std::uint8_t type, std::uint16_t id,
                                  std::uint16_t x, std::uint16_t y);

        /**
        * @brief Encode the delete entity packet
        *
        * @param packetNumber The number of the packet
        * @param id The unique id of the entity
        *
        * @return U_STRING Encoded delete entity packet
        */
        static U_STRING deleteEntity(std::uint8_t packetNumber, std::uint16_t id);

        /**
        * @brief Encode the entity movement packet
        *
        * @param packetNumber The number of the packet
        * @param id The unique id of the entity
        * @param x The new x position of the entity
        * @param y The new y position of the entity
        * @param rotation The new rotation of the entity
        *
        * @return U_STRING Encoded move entity packet
        */
        static U_STRING moveEntity(std::uint8_t packetNumber, std::uint16_t id,
                                   std::uint16_t x, std::uint16_t y,
                                   std::uint8_t rotation);

        /**
        * @brief Encode the level information packet
        *
        * @param packetNumber The number of the packet
        * @param level The level of the game
        *
        * @return U_STRING Encoded level information packet
        */
        static U_STRING infoLevel(std::uint8_t packetNumber, std::uint8_t level);

        /**
        * @brief Encode the entity information packet
        *
        * @param packetNumber The number of the packet
        * @param id The unique id of the entity
        * @param type The type of the entity
        * @param x The x position of the entity
        * @param y The y position of the entity
        * @param rotation The rotation of the entity
        * @param life The life of the entity
        *
        * @return U_STRING Encoded entity information packet
        */
        static U_STRING infoEntity(std::uint8_t packetNumber, std::uint16_t id,
                                   std::uint8_t type, std::uint16_t x,
                                   std::uint16_t y, std::uint8_t rotation,
                                   std::uint8_t life);

        /**
        * @brief Encode the player movement packet
        *
        * @param packetNumber The number of the packet
        * @param x The inputs of the player in the x axis
        * @param y The inputs of the player in the y axis
        *
        * @return U_STRING Encoded player movement packet
        */
        static U_STRING movePlayer(std::uint8_t packetNumber, std::int8_t x,
                                   std::int8_t y);

        /**
        * @brief Encode the player action packet
        *
        * @param packetNumber The number of the packet
        * actions are not defined yet
        *
        * @return U_STRING Encoded player action packet
        */
        static U_STRING actionPlayer(std::uint8_t packetNumber, bool action1,
                                     bool action2, bool action3, bool action4);

        /**
        * @brief Encode the game start packet
        *
        * @param packetNumber The number of the packet
        *
        * @return U_STRING Encoded game start packet
        */
        static U_STRING gameStart(std::uint8_t packetNumber);

        /**
        * @brief Encode the game end packet
        *
        * @param packetNumber The number of the packet
        *
        * @return U_STRING Encoded game end packet
        */
        static U_STRING gameEnd(std::uint8_t packetNumber);

        /**
        * @brief Encode the error packet
        *
        * @param packetNumber The number of the packet
        *
        * @return U_STRING Encoded error packet
        */
        static U_STRING error(std::uint8_t packetNumber);

        /**
        * @brief Encode the ACK packet
        *
        *
        * @return U_STRING Encoded ACK packet
        */
        static U_STRING ACKMissing(std::uint8_t packetNumber,
                                   std::vector<std::uint8_t> &packets);
    };
}
