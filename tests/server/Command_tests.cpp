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
    // RType::MovePlayerCommand moveCommand("Hello");
    // cr_assert_str_eq(moveCommand.getData().c_str(), "Hello");
    // cr_assert_eq(moveCommand.getType(), RType::MOVE);

    // RType::ShootCommand shootCommand("Hello");
    // cr_assert_str_eq(shootCommand.getData().c_str(), "Hello");
    // cr_assert_eq(shootCommand.getType(), RType::SHOOT);

    // RType::StartCommand startCommand("Hello");
    // cr_assert_str_eq(startCommand.getData().c_str(), "Hello");
    // cr_assert_eq(startCommand.getType(), RType::START);
}

Test(testCommand, TestCommandFactorySuccess)
{
    // RType::CommandFactory factory;

    // std::shared_ptr<RType::ICommand> moveCommand = factory.createCommand("Move 45");
    // cr_assert_str_eq(moveCommand->getData().c_str(), "45");
    // cr_assert_eq(moveCommand->getType(), RType::MOVE);
    // std::shared_ptr<RType::ICommand> shootCommand = factory.createCommand("Shoot 1");
    // cr_assert_str_eq(shootCommand->getData().c_str(), "1");
    // cr_assert_eq(shootCommand->getType(), RType::SHOOT);
    // std::shared_ptr<RType::ICommand> startCommand = factory.createCommand("Start game");
    // cr_assert_str_eq(startCommand->getData().c_str(), "game");
    // cr_assert_eq(startCommand->getType(), RType::START);
}

Test(testCommand, TestCommandFactoryFailure)
{
    // RType::CommandFactory factory;

    // std::shared_ptr<RType::ICommand> invalidCommand1 = factory.createCommand("");
    // cr_assert_eq(invalidCommand1, nullptr);
    // std::shared_ptr<RType::ICommand> invalidCommand2 = factory.createCommand("Move");
    // cr_assert_eq(invalidCommand2, nullptr);
    // std::shared_ptr<RType::ICommand> invalidCommand3 = factory.createCommand("invalid test");
    // cr_assert_eq(invalidCommand3, nullptr);
}
