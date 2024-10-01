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
    COMMAND_INFO Decoder::getCommandInfo(U_STRING &packet)
    {
        switch (getType(packet)) {
            case CONNEXION:
                return std::make_pair(CONNEXION, COMMAND_ARGS());
            case DISCONNEXION:
                return std::make_pair(DISCONNEXION, COMMAND_ARGS());
            case NEW_ENTITY:
                return std::make_pair(NEW_ENTITY, newEntity(packet));
            case DELETE_ENTITY:
                return std::make_pair(DELETE_ENTITY, deleteEntity(packet));
            case MOVE_ENTITY:
                return std::make_pair(MOVE_ENTITY, moveEntity(packet));
            case INFO_LEVEL:
                return std::make_pair(INFO_LEVEL, infoLevel(packet));
            case INFO_ENTITY:
                return std::make_pair(INFO_ENTITY, infoEntity(packet));
            case MOVE_PLAYER:
                return std::make_pair(MOVE_PLAYER, movePlayer(packet));
            case ACTION_PLAYER:
                return std::make_pair(ACTION_PLAYER, actionPlayer(packet));
            default:
                return std::make_pair(ERROR, COMMAND_ARGS());
        }
    }

    PacketType Decoder::getType(U_STRING &packet)
    {
        return static_cast<PacketType>(packet[1] & 0x3F);
    }

    std::size_t Decoder::getSize(U_STRING &packet)
    {
        return ((packet[0] << 8) | (packet[1] & 0xC0)) >> 6;
    }

    COMMAND_ARGS Decoder::newEntity(U_STRING &packet)
    {
        COMMAND_ARGS args(4);

        args[0] = packet[2];
        args[1] = packet[3];
        args[2] = (packet[4] << 8) + packet[5];
        args[3] = (packet[6] << 8) + packet[7];
        return args;
    }

    COMMAND_ARGS Decoder::deleteEntity(U_STRING &packet)
    {
        COMMAND_ARGS args(1);

        args[0] = packet[2];
        return args;
    }

    COMMAND_ARGS Decoder::moveEntity(U_STRING &packet)
    {
        COMMAND_ARGS args(4);

        args[0] = packet[2];
        args[1] = (packet[3] << 8) + packet[4];
        args[2] = (packet[5] << 8) + packet[6];
        args[3] = packet[7];
        return args;
    }

    COMMAND_ARGS Decoder::infoLevel(U_STRING &packet)
    {
        COMMAND_ARGS args(1);

        args[0] = packet[2];
        return args;
    }

    COMMAND_ARGS Decoder::infoEntity(U_STRING &packet)
    {
        COMMAND_ARGS args(6);

        args[0] = packet[2];
        args[1] = packet[3];
        args[2] = (packet[4] << 8) | packet[5];
        args[3] = (packet[6] << 8) | packet[7];
        args[4] = packet[8];
        args[5] = packet[9];
        return args;
    }

    COMMAND_ARGS Decoder::movePlayer(U_STRING &packet)
    {
        COMMAND_ARGS args(2);

        args[0] = static_cast<std::int8_t>(packet[2]);
        args[1] = static_cast<std::int8_t>(packet[3]);
        return args;
    }

    COMMAND_ARGS Decoder::actionPlayer(U_STRING &packet)
    {
        COMMAND_ARGS args(4);

        args[0] = (packet[2] >> 3) & 1;
        args[1] = (packet[2] >> 2) & 1;
        args[2] = (packet[2] >> 1) & 1;
        args[3] = packet[2] & 1;
        return args;
    }
}
