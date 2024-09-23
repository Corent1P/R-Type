/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE client main
*/

#include <iostream>
#include <array>
#include "Error.hh"
#include "client/Client.hh"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    try {
        // if (ac != 2)
        //     throw RType::Error("Invalid arguments");
        RType::Client(4242);
    } catch(std::exception &err) {
        std::cerr << err.what() << std::endl;
        return 84;
    }
    return 0;
}
