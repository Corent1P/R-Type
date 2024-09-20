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
#include "../ecs/Components/PositionComponent.hpp"
#include "../ecs/Components/HealthComponent.hpp"

int main(void)
{
    // std::cout << "Client" << std::endl;

    Coordinator coord;
    std::shared_ptr<Entity> ent = coord.generateNewEntity();
    std::shared_ptr<Entity> ent2 = coord.generateNewEntity();
    
    // for (int i = 0; i < 3; i++) {
    //     coord.generateNewEntity();
    //     coord.generateNewSystem();
    // }
    
    ent->pushComponent(std::make_shared<PositionComponent>(10, 10));
    ent->pushComponent(std::make_shared<HealthComponent>(25));

    ent2->pushComponent(std::make_shared<PositionComponent>(15, 7));
    ent2->pushComponent(std::make_shared<HealthComponent>(54));

    std::cout << "Entity1 position X: " << ent->getComponent<PositionComponent>()->getPositionX() << std::endl;
    std::cout << "Entity1 health: " << ent->getComponent<HealthComponent>()->getHealth() << std::endl;
    std::cout << "Entity2 position X: " << ent2->getComponent<PositionComponent>()->getPositionX() << std::endl;
    std::cout << "Entity2 health: " << ent2->getComponent<HealthComponent>()->getHealth() << std::endl;
}
