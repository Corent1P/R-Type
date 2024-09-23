/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE client main
*/

#include <iostream>
#include <array>

#include "../ecs/Coordinator.hpp"
#include "../ecs/Components/PositionComponent.hpp"
#include "../ecs/Components/HealthComponent.hpp"

int main(void)
{
    Coordinator coord;
    std::shared_ptr<Entity> ent = coord.generateNewEntity();
    std::shared_ptr<Entity> ent2 = coord.generateNewEntity();
    
    ent->pushComponent(std::make_shared<PositionComponent>(10, 10));
    ent->pushComponent(std::make_shared<HealthComponent>(25));

    ent2->pushComponent(std::make_shared<PositionComponent>(15, 7));
    ent2->pushComponent(std::make_shared<HealthComponent>(54));

    std::cout << coord << std::endl;
}
