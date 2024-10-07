/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** encoder_test
*/

#include "../Criterion.hh"

#include "../../src/protocolHandler/Encoder.hh"
#include <criterion/internal/assert.h>

Test(main, TestEncoderHeader) {
    U_STRING testString;
    U_STRING outputString;

    testString += '\0';
    testString += '\0';
    testString += 1;
    outputString = RType::Encoder::header(1, 0, RType::CONNEXION);
    cr_assert_eq(testString, outputString, "Expected: 0000000000000000, Got: %08b%08b",
                 outputString[0], outputString[1]);

    testString.clear();
    testString += 0b00001010;
    testString += 0b10001000;
    testString += 13;
    outputString = RType::Encoder::header(13, 42, RType::ACTION_PLAYER);
    cr_assert_eq(testString, outputString, "Expected: 0000101010001000, Got: %08b%08b",
                 outputString[0], outputString[1]);

    testString.clear();
    testString += 0b00000101;
    testString += 0b01000101;
    testString += 32;
    outputString = RType::Encoder::header(32, 21, RType::INFO_LEVEL);
    cr_assert_eq(testString, outputString, "Expected: 0000101010001000, Got: %08b%08b",
                 outputString[0], outputString[1]);
}

Test(main, TestConnexionPacket) {
    U_STRING testString;
    U_STRING outputString;

    testString += '\0';
    testString += '\0';
    testString += 12;
    outputString = RType::Encoder::connexion(12);
    cr_assert_eq(testString, outputString, "Expected: 0000000000000000, Got: %08b%08b",
                 outputString[0], outputString[1]);
}

Test(main, TestDisconnexionPacket) {
    U_STRING testString;
    U_STRING outputString;

    testString += '\0';
    testString += 1;
    testString += 12;
    outputString = RType::Encoder::disconnexion(12);
    cr_assert_eq(testString, outputString, "Expected: 0000000000000001, Got: %08b%08b",
                 outputString[0], outputString[1]);
}
