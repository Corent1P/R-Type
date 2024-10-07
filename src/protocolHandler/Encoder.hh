/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Encoder
*/

#pragma once

#include <cstdint>
#include <iostream>
#include <stdbool.h>

#define U_STRING std::basic_string<unsigned char>

namespace RType {

    /**
    * @brief Enum to define the type of the packet
    */
    enum PacketType {
        ERROR = -1,
        CONNEXION = 0,
        DISCONNEXION = 1,
        NEW_ENTITY = 2,
        DELETE_ENTITY = 3,
        MOVE_ENTITY = 4,
        INFO_LEVEL = 5,
        INFO_ENTITY = 6,
        MOVE_PLAYER = 7,
        ACTION_PLAYER = 8,
        GAME_START = 9,
        GAME_END = 10,
    };

    /**
    * @brief Class to encode the data to communicate with the client and the server
    */
    class Encoder {
    public:
        /**
        * @brief Encode the header of the packet
        *
        * @param size Total size of the packet, excluding the header
        * @param type Type of the packet
        *
        * @return U_STRING Encoded header
        */
        static U_STRING header(std::uint16_t size, unsigned char type);

        /**
        * @brief Encode the connexion packet
        *
        * @return U_STRING Encoded connexion packet
        */
        static U_STRING connexion();

        /**
        * @brief Encode the disconnexion packet
        *
        * @return U_STRING Encoded disconnexion packet
        */
        static U_STRING disconnexion();

        /**
        * @brief Encode the new entity packet
        *
        * @param type Type of the entity
        * @param id The unique id of the entity
        * @param x The x position of the entity
        * @param y The y position of the entity
        *
        * @return U_STRING Encoded new entity packet
        */
        static U_STRING newEntity(std::uint8_t type, std::uint8_t id,
                                  std::uint16_t x, std::uint16_t y);

        /**
        * @brief Encode the delete entity packet
        *
        * @param id The unique id of the entity
        *
        * @return U_STRING Encoded delete entity packet
        */
        static U_STRING deleteEntity(std::uint8_t id);

        /**
        * @brief Encode the entity movement packet
        *
        * @param id The unique id of the entity
        * @param x The new x position of the entity
        * @param y The new y position of the entity
        * @param rotation The new rotation of the entity
        *
        * @return U_STRING Encoded move entity packet
        */
        static U_STRING moveEntity(std::uint8_t id, std::uint16_t x,
                                  std::uint16_t y, std::uint8_t rotation);

        /**
        * @brief Encode the level information packet
        *
        * @param level The level of the game
        *
        * @return U_STRING Encoded level information packet
        */
        static U_STRING infoLevel(std::uint8_t level);

        /**
        * @brief Encode the entity information packet
        *
        * @param id The unique id of the entity
        * @param type The type of the entity
        * @param x The x position of the entity
        * @param y The y position of the entity
        * @param rotation The rotation of the entity
        * @param life The life of the entity
        *
        * @return U_STRING Encoded entity information packet
        */
        static U_STRING infoEntity(std::uint8_t id, std::uint8_t type,
                                  std::uint16_t x, std::uint16_t y,
                                  std::uint8_t rotation, std::uint8_t life);

        /**
        * @brief Encode the player movement packet
        *
        * @param x The inputs of the player in the x axis
        * @param y The inputs of the player in the y axis
        *
        * @return U_STRING Encoded player movement packet
        */
        static U_STRING movePlayer(std::int8_t x, std::int8_t y);

        /**
        * @brief Encode the player action packet
        *
        * actions are not defined yet
        *
        * @return U_STRING Encoded player action packet
        */
        static U_STRING actionPlayer(bool action1, bool action2, bool action3,
                                    bool action4);

        /**
        * @brief Encode the game start packet
        *
        * @return U_STRING Encoded game start packet
        */
        static U_STRING gameStart();

        /**
        * @brief Encode the game end packet
        *
        * @return U_STRING Encoded game end packet
        */
        static U_STRING gameEnd();
    };
}
