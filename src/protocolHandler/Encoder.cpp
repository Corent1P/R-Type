/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Encoder
*/

#include "Encoder.hh"

namespace RType {
    U_STRING Encoder::addPacketNumber(const U_STRING &packet, std::uint16_t number)
    {
        U_STRING encodedWithNumber = packet;

        encodedWithNumber[2] = number >> 8;
        encodedWithNumber[3] = number & 0xff;
        return encodedWithNumber;
    }

    U_STRING Encoder::header(std::uint16_t size, unsigned char type)
    {
        std::uint16_t header = (size << 6) | type;
        U_STRING encodedHeader;

        encodedHeader += header >> 8;
        encodedHeader += header & 0xff;
        encodedHeader += '\0';
        encodedHeader += '\0';
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

    U_STRING Encoder::newEntity(std::uint8_t type, std::uint16_t id,
                                std::uint16_t x, std::uint16_t y,
                                std::uint16_t entityToFollow)
    {
        U_STRING encodedEntity;

        encodedEntity += type;
        encodedEntity += id >> 8;
        encodedEntity += id & 0xff;
        encodedEntity += x >> 8;
        encodedEntity += x & 0xff;
        encodedEntity += y >> 8;
        encodedEntity += y & 0xff;
        encodedEntity += entityToFollow >> 8;
        encodedEntity += entityToFollow % 0xff;
        return header(encodedEntity.size(), NEW_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::deleteEntity(std::uint16_t id)
    {
        U_STRING encodedEntity;

        encodedEntity += id >> 8;
        encodedEntity += id & 0xff;
        return header(encodedEntity.size(), DELETE_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::moveEntity(std::uint16_t id, std::uint16_t x,
                                std::uint16_t y, std::uint8_t rotation)
    {
        U_STRING encodedEntity;

        encodedEntity += id >> 8;
        encodedEntity += id & 0xff;
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

    U_STRING Encoder::infoEntity(std::uint16_t id, std::uint8_t type,
                                std::uint16_t x, std::uint16_t y,
                                std::uint8_t rotation, std::uint8_t life)
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
        return header(encodedEntity.size(), INFO_ENTITY) + encodedEntity;
    }

    U_STRING Encoder::movePlayer(std::int8_t x, std::int8_t y)
    {
        U_STRING encodedPlayer;

        encodedPlayer += static_cast<std::uint8_t>(x);
        encodedPlayer += static_cast<std::uint8_t>(y);
        return header(encodedPlayer.size(), MOVE_PLAYER) + encodedPlayer;
    }

    U_STRING Encoder::actionPlayer(bool action1, bool action2, bool action3,
                                bool action4)
    {
        U_STRING encodedPlayer;

        encodedPlayer += action1 << 3 | action2 << 2 | action3 << 1 | action4;
        return header(encodedPlayer.size(), ACTION_PLAYER) + encodedPlayer;
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

    U_STRING Encoder::ACKMissing(std::vector<std::uint16_t> packets)
    {
        U_STRING encoded;
        std::vector<std::uint8_t> chars(MAX_PACKETS / 8, 0);
        std::size_t smallestSuite = 0;
        std::size_t biggestPacket = 0;
        std::size_t packetSize = 0;

        if (packets.size() == 0)
            return header(encoded.size(), ACK_MISSING);
        biggestPacket = packets.back();
        packetSize = packets.size();
        std::sort(packets.begin(), packets.end());
        while (smallestSuite == packets[0]) {
            smallestSuite++;
            packets.erase(packets.begin());
        }
        encoded += smallestSuite >> 8;
        encoded += smallestSuite & 0xff;
        if (smallestSuite == packetSize)
            return header(encoded.size(), ACK_MISSING) + encoded;
        for (auto packet : packets) {
            packet -= smallestSuite;
            if (packet == biggestPacket)
                break;
            chars[packet / 8] += 1 << (packet % 8);
        }
        chars.resize(biggestPacket / 8 + 1);
        for (auto char_ : chars)
            encoded += char_;
        encoded += biggestPacket >> 8;
        encoded += biggestPacket & 0xff;
        return header(encoded.size(), ACK_MISSING) + encoded;
    }
}
