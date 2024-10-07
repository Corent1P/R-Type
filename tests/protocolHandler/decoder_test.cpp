/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** decoder_test
*/

#include "../Criterion.hh"

#include "../../src/protocolHandler/Decoder.hh"
#include <criterion/internal/assert.h>

Test(main, TestHeaderDecoder) {
    U_STRING packetHeader = RType::Encoder::header(70, RType::CONNEXION);

    cr_assert_eq(RType::Decoder::getType(packetHeader), RType::CONNEXION);
    cr_assert_eq(RType::Decoder::getSize(packetHeader), 70, "Expected: 70, Got: %lu",
                 RType::Decoder::getSize(packetHeader));

    packetHeader = RType::Encoder::header(42, RType::ACTION_PLAYER);
    cr_assert_eq(RType::Decoder::getType(packetHeader), RType::ACTION_PLAYER);
    cr_assert_eq(RType::Decoder::getSize(packetHeader), 42, "Expected: 42, Got: %lu",
                 RType::Decoder::getSize(packetHeader));
}

Test(main, TestNewEntityPacketDecoder) {
    U_STRING packet = RType::Encoder::newEntity(1, 2, 3, 4);
    COMMAND_ARGS args = RType::Decoder::newEntity(packet);

    cr_assert_eq(args[0], 1, "Expected: 1, Got: %lu", args[0]);
    cr_assert_eq(args[1], 2, "Expected: 2, Got: %lu", args[1]);
    cr_assert_eq(args[2], 3, "Expected: 3, Got: %lu", args[2]);
    cr_assert_eq(args[3], 4, "Expected: 4, Got: %lu", args[3]);
}

Test(main, TestDeleteEntityPacketDecoder) {
    U_STRING packet = RType::Encoder::deleteEntity(1);
    COMMAND_ARGS args = RType::Decoder::deleteEntity(packet);

    cr_assert_eq(args[0], 1, "Expected: 1, Got: %lu", args[0]);
}

Test(main, TestMoveEntityPacketDecoder) {
    U_STRING packet = RType::Encoder::moveEntity(1, 2, 3, 4);
    COMMAND_ARGS args = RType::Decoder::moveEntity(packet);

    cr_assert_eq(args[0], 1, "Expected: 1, Got: %lu", args[0]);
    cr_assert_eq(args[1], 2, "Expected: 2, Got: %lu", args[1]);
    cr_assert_eq(args[2], 3, "Expected: 3, Got: %lu", args[2]);
    cr_assert_eq(args[3], 4, "Expected: 4, Got: %lu", args[3]);
}

Test(main, TestInfoLevelPacketDecoder) {
    U_STRING packet = RType::Encoder::infoLevel(17);
    COMMAND_ARGS args = RType::Decoder::infoLevel(packet);

    cr_assert_eq(args[0], 17, "Expected: 17, Got: %lu", args[0]);
}

Test(main, TestInfoEntityPacketDecoder) {
    U_STRING packet = RType::Encoder::infoEntity(2, 23, 345, 12, 0, 123);
    COMMAND_ARGS args = RType::Decoder::infoEntity(packet);

    cr_assert_eq(args[0], 2, "Expected: 2, Got: %lu", args[0]);
    cr_assert_eq(args[1], 23, "Expected: 23, Got: %lu", args[1]);
    cr_assert_eq(args[2], 345, "Expected: 345, Got: %lu", args[2]);
    cr_assert_eq(args[3], 12, "Expected: 12, Got: %lu", args[3]);
    cr_assert_eq(args[4], 0, "Expected: 0, Got: %lu", args[4]);
    cr_assert_eq(args[5], 123, "Expected: 123, Got: %lu", args[5]);
}

Test(main, TestMovePlayerPacketDecoder) {
    U_STRING packet = RType::Encoder::movePlayer(45, 12);
    COMMAND_ARGS args = RType::Decoder::movePlayer(packet);

    cr_assert_eq(args[0], 45, "Expected: 45, Got: %lu", args[0]);
    cr_assert_eq(args[1], 12, "Expected: 12, Got: %lu", args[1]);
    packet = RType::Encoder::movePlayer(-100, -100);
    args = RType::Decoder::movePlayer(packet);
    cr_assert_eq(args[0], -100, "Expected: -100, Got: %ld", args[0]);
    cr_assert_eq(args[1], -100, "Expected: -100, Got: %ld", args[1]);
}

Test(main, TestActionPlayerPacketDecoder) {
    U_STRING packet = RType::Encoder::actionPlayer(false, true, false, true);
    COMMAND_ARGS args = RType::Decoder::actionPlayer(packet);

    cr_assert_eq(args[0], 0, "Expected: 0, Got: %lu", args[0]);
    cr_assert_eq(args[1], 1, "Expected: 1, Got: %lu", args[1]);
    cr_assert_eq(args[2], 0, "Expected: 0, Got: %lu", args[2]);
    cr_assert_eq(args[3], 1, "Expected: 1, Got: %lu", args[3]);
}

Test(main, TestGameStartPacketDecoder) {
    U_STRING packetHeader = RType::Encoder::header(70, RType::GAME_START);

    cr_assert_eq(RType::Decoder::getType(packetHeader), RType::GAME_START);
    cr_assert_eq(RType::Decoder::getSize(packetHeader), 70, "Expected: 70, Got: %lu",
                 RType::Decoder::getSize(packetHeader));
}

Test(main, TestGameEndPacketDecoder) {
    U_STRING packetHeader = RType::Encoder::header(70, RType::GAME_END);

    cr_assert_eq(RType::Decoder::getType(packetHeader), RType::GAME_END);
    cr_assert_eq(RType::Decoder::getSize(packetHeader), 70, "Expected: 70, Got: %lu",
                 RType::Decoder::getSize(packetHeader));
}
