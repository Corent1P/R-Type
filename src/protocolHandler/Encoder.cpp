/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Encoder
*/

#include "Encoder.hh"

namespace RType {
    U_STRING Encoder::header(std::uint16_t size, unsigned char type)
    {
        std::uint16_t header = (size << 6) | type;
        std::basic_string<unsigned char> encodedHeader;

        encodedHeader += header >> 8;
        encodedHeader += header & 0xff;
        return encodedHeader;
    }

    U_STRING Encoder::connexion()
    {
        return header(0, CONNEXION);
    }

    U_STRING Encoder::disconnexion()
    {
        return header(0, DISCONNEXION);
    }

    U_STRING Encoder::newEntity(std::uint8_t type, std::uint8_t id,
                                std::uint16_t x, std::uint16_t y)
    {
        U_STRING encodedEntity;

        encodedEntity += type;
        encodedEntity += id;
        encodedEntity += x >> 8;
        encodedEntity += x & 0xff;
        encodedEntity += y >> 8;
        encodedEntity += y & 0xff;
        return header(encodedEntity.size(), NEW_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::deleteEntity(std::uint8_t id)
    {
        U_STRING encodedEntity;

        encodedEntity += id;
        return header(encodedEntity.size(), DELETE_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::moveEntity(std::uint8_t id, std::uint16_t x,
                                std::uint16_t y, std::uint8_t rotation)
    {
        U_STRING encodedEntity;

        encodedEntity += id;
        encodedEntity += x >> 8;
        encodedEntity += x & 0xff;
        encodedEntity += y >> 8;
        encodedEntity += y & 0xff;
        encodedEntity += rotation;
        return header(encodedEntity.size(), MOVE_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::infoLevel(std::uint8_t level)
    {
        U_STRING encodedLevel;

        encodedLevel += level;
        return header(encodedLevel.size(), INFO_LEVEL) + encodedLevel;
    }

    U_STRING Encoder::infoEntity(std::uint8_t id, std::uint8_t type,
                                std::uint16_t x, std::uint16_t y,
                                std::uint8_t rotation, std::uint8_t life)
    {
        U_STRING encodedEntity;

        encodedEntity += id;
        encodedEntity += type;
        encodedEntity += x >> 8;
        encodedEntity += x & 0xff;
        encodedEntity += y >> 8;
        encodedEntity += y & 0xff;
        encodedEntity += rotation;
        encodedEntity += life;
        return header(encodedEntity.size(), INFO_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::movePlayer(std::int16_t x, std::int16_t y)
    {
        U_STRING encodedPlayer;

        encodedPlayer += x >> 8;
        encodedPlayer += x & 0xff;
        encodedPlayer += y >> 8;
        encodedPlayer += y & 0xff;
        return header(encodedPlayer.size(), MOVE_PLAYER) + encodedPlayer;
    }

    U_STRING Encoder::actionPlayer(bool action1, bool action2, bool action3,
                                bool action4)
    {
        U_STRING encodedPlayer;

        encodedPlayer += action1 << 3 | action2 << 2 | action3 << 1 | action4;
        return header(encodedPlayer.size(), ACTION_PLAYER) + encodedPlayer;
    }
}
