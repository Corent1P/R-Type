/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Encoder
*/

#include "Encoder.hh"
#include <array>
#include <bitset>
#include <cstdint>
#include <vector>

namespace RType {

    U_STRING Encoder::addPacketNumber(U_STRING &packet, std::uint8_t number)
    {
        packet.insert(packet.begin(), number);
        return packet;
    }

    U_STRING Encoder::header(const std::uint16_t &size, const unsigned char &type)
    {
        std::uint16_t header = (size << 6) | type;
        U_STRING encoded;

        encoded += header >> 8;
        encoded += header & 0xff;
        return encoded;
    }

    U_STRING Encoder::connexion()
    {
        return header(0, CONNEXION);
    }

    U_STRING Encoder::disconnexion()
    {
        return header(0, DISCONNEXION);
    }

    U_STRING Encoder::newEntity(const std::uint8_t &type, const std::uint16_t &id,
                                const std::uint16_t &x, const std::uint16_t &y)
    {
        U_STRING encoded;

        encoded += type;
        encoded += id >> 8;
        encoded += id & 0xff;
        encoded += x >> 8;
        encoded += x & 0xff;
        encoded += y >> 8;
        encoded += y & 0xff;
        return header(encoded.size(), NEW_ENTITY) + encoded;
    }

    U_STRING Encoder::deleteEntity(const std::uint16_t &id)
    {
        U_STRING encoded;

        encoded += id >> 8;
        encoded += id & 0xff;
        return header(encoded.size(), DELETE_ENTITY) + encoded;
    }

    U_STRING Encoder::moveEntity(const std::uint16_t &id,
                                 const std::uint16_t &x, const std::uint16_t &y,
                                 const std::uint8_t &rotation)
    {
        U_STRING encoded;

        encoded += id >> 8;
        encoded += id & 0xff;
        encoded += x >> 8;
        encoded += x & 0xff;
        encoded += y >> 8;
        encoded += y & 0xff;
        encoded += rotation;
        return header(encoded.size(), MOVE_ENTITY) + encoded;
    }

    U_STRING Encoder::infoLevel(const std::uint8_t &level)
    {
        U_STRING encoded;

        encoded += level;
        return header(encoded.size(), INFO_LEVEL) + encoded;
    }

    U_STRING Encoder::infoEntity(const std::uint16_t &id,
                                 const std::uint8_t &type, const std::uint16_t &x,
                                 const std::uint16_t &y, const std::uint8_t &rotation,
                                 const std::uint8_t &life)
    {
        U_STRING encoded;

        encoded += id >> 8;
        encoded += id & 0xff;
        encoded += type;
        encoded += x >> 8;
        encoded += x & 0xff;
        encoded += y >> 8;
        encoded += y & 0xff;
        encoded += rotation;
        encoded += life;
        return header(encoded.size(), INFO_ENTITY) + encoded;
    }

    U_STRING Encoder::movePlayer(const std::int8_t &x, const std::int8_t &y)
    {
        U_STRING encoded;

        encoded += static_cast<std::uint8_t>(x);
        encoded += static_cast<std::uint8_t>(y);
        return header(encoded.size(), MOVE_PLAYER) + encoded;
    }

    U_STRING Encoder::actionPlayer(const bool &action1, const bool &action2,
                                   const bool &action3, const bool &action4)
    {
        U_STRING encoded;

        encoded += action1 << 3 | action2 << 2 | action3 << 1 | action4;
        return header(encoded.size(), ACTION_PLAYER) + encoded;
    }

    U_STRING Encoder::gameStart()
    {
        return header(0, GAME_START);
    }

    U_STRING Encoder::gameEnd()
    {
        return header(0, GAME_END);
    }

    U_STRING Encoder::error()
    {
        return header(0, PACKET_ERROR);
    }

    U_STRING Encoder::ACKMissing(const std::vector<std::uint8_t> &packets)
    {
        U_STRING encoded;
        std::vector<std::uint8_t> chars(PACKET_MAX / 8, 0);

        for (std::uint8_t packet : packets)
            chars[packet / 8] += 1 << (packet % 8);
        for (std::size_t i = 0; i < PACKET_MAX / 8; i++)
            encoded += chars[i];
        return header(encoded.size(), ACK_MISSING) +
               encoded;
    }
}
