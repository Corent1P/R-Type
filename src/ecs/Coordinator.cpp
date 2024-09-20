/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ECS Coordinator for Components & systems
*/

#include "Coordinator.hpp"

Coordinator::Coordinator():
    _idEntities(0)
{
}

std::shared_ptr<Entity> Coordinator::generateNewEntity() {
    std::shared_ptr<Entity> newEntity = std::make_unique<Entity>(_idEntities++);
    _entities.push_back(newEntity);
    return (newEntity);
}

void Coordinator::generateNewSystem() {
    _systems.push_back(std::make_unique<ASystem>());
}

std::vector<std::shared_ptr<Entity>> Coordinator::getEntities() const
{
    return _entities;
}

std::vector<std::shared_ptr<ISystem>> Coordinator::getSystems() const
{
    return _systems;
}

// std::ostream &operator<<(std::ostream &s, const Coordinator &coordinator)
// {
// 	std::vector<std::shared_ptr<Entity>> entities = coordinator.getEntities();
// 	std::vector<std::shared_ptr<ISystem>> systems = coordinator.getSystems();

//     s << "Coordinator:\n";
//     for (auto entity: entities)
//         s << "\t" << *entity;
//     s << std::endl;
//     for (auto system: systems)
//         s << "\t" << *system;
//     return s;
// }
