/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Encoder
*/

#include "Encoder.hh"

namespace RType {
    U_STRING Encoder::header(std::uint8_t packetNumber, std::uint16_t size,
                             unsigned char type)
    {
        std::uint16_t header = (size << 6) | type;
        U_STRING encodedHeader;

        encodedHeader += header >> 8;
        encodedHeader += header & 0xff;
        encodedHeader += packetNumber;
        return encodedHeader;
    }

    U_STRING Encoder::connexion(std::uint8_t packetNumber)
    {
        return header(packetNumber, 0, CONNEXION);
    }

    U_STRING Encoder::disconnexion(std::uint8_t packetNumber)
    {
        return header(packetNumber, 0, DISCONNEXION);
    }

    U_STRING Encoder::newEntity(std::uint8_t packetNumber, std::uint8_t type,
                                std::uint16_t id, std::uint16_t x, std::uint16_t y)
    {
        U_STRING encodedEntity;

        encodedEntity += type;
        encodedEntity += id >> 8;
        encodedEntity += id & 0xff;
        encodedEntity += x >> 8;
        encodedEntity += x & 0xff;
        encodedEntity += y >> 8;
        encodedEntity += y & 0xff;
        return header(packetNumber, encodedEntity.size(), NEW_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::deleteEntity(std::uint8_t packetNumber, std::uint16_t id)
    {
        U_STRING encodedEntity;

        encodedEntity += id >> 8;
        encodedEntity += id & 0xff;
        return header(packetNumber, encodedEntity.size(), DELETE_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::moveEntity(std::uint8_t packetNumber, std::uint16_t id,
                                 std::uint16_t x, std::uint16_t y,
                                 std::uint8_t rotation)
    {
        U_STRING encodedEntity;

        encodedEntity += id >> 8;
        encodedEntity += id & 0xff;
        encodedEntity += x >> 8;
        encodedEntity += x & 0xff;
        encodedEntity += y >> 8;
        encodedEntity += y & 0xff;
        encodedEntity += rotation;
        return header(packetNumber, encodedEntity.size(), MOVE_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::infoLevel(std::uint8_t packetNumber, std::uint8_t level)
    {
        U_STRING encodedLevel;

        encodedLevel += level;
        return header(packetNumber, encodedLevel.size(), INFO_LEVEL) + encodedLevel;
    }

    U_STRING Encoder::infoEntity(std::uint8_t packetNumber, std::uint16_t id,
                                 std::uint8_t type, std::uint16_t x,
                                 std::uint16_t y, std::uint8_t rotation,
                                 std::uint8_t life)
    {
        U_STRING encodedEntity;

        encodedEntity += id >> 8;
        encodedEntity += id & 0xff;
        encodedEntity += type;
        encodedEntity += x >> 8;
        encodedEntity += x & 0xff;
        encodedEntity += y >> 8;
        encodedEntity += y & 0xff;
        encodedEntity += rotation;
        encodedEntity += life;
        return header(packetNumber, encodedEntity.size(), INFO_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::movePlayer(std::uint8_t packetNumber, std::int8_t x,
                                 std::int8_t y)
    {
        U_STRING encodedPlayer;

        encodedPlayer += static_cast<std::uint8_t>(x);
        encodedPlayer += static_cast<std::uint8_t>(y);
        return header(packetNumber, encodedPlayer.size(), MOVE_PLAYER) + encodedPlayer;
    }

    U_STRING Encoder::actionPlayer(std::uint8_t packetNumber, bool action1,
                                   bool action2, bool action3, bool action4)
    {
        U_STRING encodedPlayer;

        encodedPlayer += action1 << 3 | action2 << 2 | action3 << 1 | action4;
        return header(packetNumber, encodedPlayer.size(), ACTION_PLAYER) + encodedPlayer;
    }

    U_STRING Encoder::gameStart(std::uint8_t packetNumber)
    {
        return header(packetNumber, 0, GAME_START);
    }

    U_STRING Encoder::gameEnd(std::uint8_t packetNumber)
    {
        return header(packetNumber, 0, GAME_END);
    }

    U_STRING Encoder::error(std::uint8_t packetNumber)
    {
        return header(packetNumber, 0, ERROR);
    }
}
