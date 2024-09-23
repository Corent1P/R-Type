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
#include "../ecs/Components/EntityTypeComponent.hpp"

int main(void)
{
    RType::Coordinator coord;
    std::shared_ptr<RType::Entity> ent = coord.generateNewEntity();
    std::shared_ptr<RType::Entity> ent2 = coord.generateNewEntity();
    
    ent->pushComponent(std::make_shared<RType::PositionComponent>(10, 10));
    ent->pushComponent(std::make_shared<RType::HealthComponent>(25));
    ent->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::PLAYER));

    ent2->pushComponent(std::make_shared<RType::PositionComponent>(15, 7));
    ent2->pushComponent(std::make_shared<RType::HealthComponent>(54));
    ent2->pushComponent(std::make_shared<RType::EntityTypeComponent>(RType::MOB));

    std::cout << coord << std::endl;
}
