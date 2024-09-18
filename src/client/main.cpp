/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE client main
*/

#include <iostream>
#include <array>

#include "../ecs/Coordinator.hpp"
#include "../ecs/AComponent.hpp"

int main(void)
{
    std::cout << "Client" << std::endl;

    Coordinator coord;
    for (int i = 0; i < 3; i++) {
        coord.generateNewEntity();
        coord.generateNewSystem();
    }
    std::shared_ptr<IComponent> component = std::make_unique<AComponent>();
    coord.getEntities()[0]->pushComponent(component);

    std::cout << coord << std::endl;
}
