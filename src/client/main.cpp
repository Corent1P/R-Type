/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE client main
*/

#include <iostream>
#include <array>

#include "Game.hh"

int main(void)
{
    try {
        RType::Game game;
        std::cout << game;
        game.gameLoop();
    }  catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
