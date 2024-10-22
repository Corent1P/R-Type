/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Decoder
*/

#include "Decoder.hh"
#include "Encoder.hh"
#include <utility>

namespace RType {
    PACKET Decoder::getCommandInfo(U_STRING &packet)
    {
        switch (getType(packet)) {
            case CONNEXION:
                return std::make_pair(decryptHeader(packet), COMMAND_ARGS());
            case DISCONNEXION:
                return std::make_pair(decryptHeader(packet), COMMAND_ARGS());
            case CONNEXION_CONFIRM:
                return std::make_pair(decryptHeader(packet), COMMAND_ARGS());
            case ACK_MISSING:
                return std::make_pair(decryptHeader(packet), ACKMissing(packet));
            case GAME_START:
                return std::make_pair(decryptHeader(packet), COMMAND_ARGS());
            case GAME_END:
                return std::make_pair(decryptHeader(packet), COMMAND_ARGS());
            case INFO_LEVEL:
                return std::make_pair(decryptHeader(packet), infoLevel(packet));
            case NEW_ENTITY:
                return std::make_pair(decryptHeader(packet), newEntity(packet));
            case DELETE_ENTITY:
                return std::make_pair(decryptHeader(packet), deleteEntity(packet));
            case MOVE_ENTITY:
                return std::make_pair(decryptHeader(packet), moveEntity(packet));
            case INFO_ENTITY:
                return std::make_pair(decryptHeader(packet), infoEntity(packet));
            case MOVE_PLAYER:
                return std::make_pair(decryptHeader(packet), movePlayer(packet));
            case ACTION_PLAYER:
                return std::make_pair(decryptHeader(packet), actionPlayer(packet));
            case PACKET_ERROR:
                return std::make_pair(decryptHeader(packet), COMMAND_ARGS());
            default:
                return std::make_pair(UNKNOWN_HEADER, COMMAND_ARGS());
        }
    }

    PacketType Decoder::getType(const U_STRING &packet)
    {
        return static_cast<PacketType>(packet[1] & 0x3F);
    }

    std::size_t Decoder::getSize(U_STRING &packet)
    {
        return ((packet[0] << 8) | (packet[1] & 0xC0)) >> 6;
    }

    std::uint8_t Decoder::getPacketNumber(const U_STRING &packet)
    {
        return packet[2];
    }

    HEADER Decoder::decryptHeader(U_STRING &packet)
    {
        return std::make_pair(getType(packet), getPacketNumber(packet));
    }

    COMMAND_ARGS Decoder::newEntity(U_STRING &packet)
    {
        COMMAND_ARGS args(4);

        args[0] = packet[3];
        args[1] = (packet[4] << 8) + packet[5];
        args[2] = (packet[6] << 8) + packet[7];
        args[3] = (packet[8] << 8) + packet[9];
        return args;
    }

    COMMAND_ARGS Decoder::deleteEntity(U_STRING &packet)
    {
        COMMAND_ARGS args(1);

        args[0] = (packet[3] << 8) + packet[4];
        return args;
    }

    COMMAND_ARGS Decoder::moveEntity(U_STRING &packet)
    {
        COMMAND_ARGS args(4);

        args[0] = (packet[3] << 8) + packet[4];
        args[1] = (packet[5] << 8) + packet[6];
        args[2] = (packet[7] << 8) + packet[8];
        args[3] = packet[9];
        return args;
    }

    COMMAND_ARGS Decoder::infoLevel(U_STRING &packet)
    {
        COMMAND_ARGS args(1);

        args[0] = packet[3];
        return args;
    }

    COMMAND_ARGS Decoder::infoEntity(U_STRING &packet)
    {
        COMMAND_ARGS args(6);

        args[0] = (packet[3] << 8) + packet[4];
        args[1] = packet[5];
        args[2] = (packet[6] << 8) | packet[7];
        args[3] = (packet[8] << 8) | packet[9];
        args[4] = packet[10];
        args[5] = packet[11];
        return args;
    }

    COMMAND_ARGS Decoder::movePlayer(U_STRING &packet)
    {
        COMMAND_ARGS args(2);

        args[0] = static_cast<std::int8_t>(packet[3]);
        args[1] = static_cast<std::int8_t>(packet[4]);
        return args;
    }

    COMMAND_ARGS Decoder::actionPlayer(U_STRING &packet)
    {
        COMMAND_ARGS args(4);

        args[0] = (packet[3] >> 3) & 1;
        args[1] = (packet[3] >> 2) & 1;
        args[2] = (packet[3] >> 1) & 1;
        args[3] = packet[3] & 1;
        return args;
    }

    COMMAND_ARGS Decoder::ACKMissing(U_STRING &packet)
    {
        COMMAND_ARGS args(MAX_PACKETS);
        std::uint8_t nbMissing = 0;

        for (std::size_t i = 0; i < MAX_PACKETS; i++) {
            if ((packet[i / 8 + 3] & (1 << (i % 8))) != 0) {
                args[nbMissing] = i;
                nbMissing++;
            }
        }
        args.resize(nbMissing);
        return args;
    }
}
