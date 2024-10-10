/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_tests
*/

#include "../Criterion.hh"

#include "../../src/server/command/factory/CommandFactory.hh"

Test(testCommand, TestCommandCreation)
{
    auto encoderMove = RType::Encoder::movePlayer(45, 6);
    RType::MovePlayerCommand moveCommand(RType::Decoder::movePlayer(encoderMove));
    cr_assert_eq(moveCommand.getData()[0], 45);
    cr_assert_eq(moveCommand.getData()[1], 6);
    cr_assert_eq(moveCommand.getType(), RType::MOVE_PLAYER);
}

Test(testCommand, TestCommandFactorySuccess)
{
    RType::CommandFactory factory;

    auto encoderMove = RType::Encoder::movePlayer(45, 6);
    std::shared_ptr<RType::ICommand> moveCommand = factory.createCommand(RType::Decoder::getCommandInfo(encoderMove));
    cr_assert_eq(moveCommand->getData()[0], 45);
    cr_assert_eq(moveCommand->getData()[1], 6);
    cr_assert_eq(moveCommand->getType(), RType::MOVE_PLAYER);

    auto encoderActionPlayer = RType::Encoder::actionPlayer(true, false, false, false);
    std::shared_ptr<RType::ICommand> actionCommand = factory.createCommand(RType::Decoder::getCommandInfo(encoderActionPlayer));
    cr_assert_eq(actionCommand->getData()[0], true);
    cr_assert_eq(actionCommand->getData()[1], false);
    cr_assert_eq(actionCommand->getType(), RType::ACTION_PLAYER);
}

Test(testCommand, TestCommandFactoryFailure)
{
    RType::CommandFactory factory;

    auto encoderConnection = RType::Encoder::connexion();
    std::shared_ptr<RType::ICommand> connectionCommand = factory.createCommand(RType::Decoder::getCommandInfo(encoderConnection));
    cr_assert_eq(connectionCommand, nullptr);

    auto encoderDisconnection = RType::Encoder::disconnexion();
    std::shared_ptr<RType::ICommand> disconnectionCommand = factory.createCommand(RType::Decoder::getCommandInfo(encoderDisconnection));
    cr_assert_eq(disconnectionCommand, nullptr);

    // TODO: test if the factory returns nullptr when the command is not found
}
