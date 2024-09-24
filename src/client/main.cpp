/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** R-TYPE client main
*/

#include <iostream>
#include <array>

#include "../ecs/Coordinator.hh"
#include "../ecs/Components/PositionComponent.hh"
#include "../ecs/Components/HealthComponent.hh"
#include "../ecs/Components/EntityTypeComponent.hh"

int main(void)
{
    std::cout << "chien" << std::endl;
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
