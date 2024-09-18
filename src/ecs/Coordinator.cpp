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

void Coordinator::generateNewEntity() {
    _entities.push_back(std::make_unique<Entity>(_idEntities++));
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

std::ostream &operator<<(std::ostream &s, const Coordinator &coordinator)
{
	std::vector<std::shared_ptr<Entity>> entities = coordinator.getEntities();
	std::vector<std::shared_ptr<ISystem>> systems = coordinator.getSystems();

    s << "Coordinator:\n";
    for (auto entity: entities)
        s << *entity << std::endl;
    for (auto system: systems)
        s << system << std::endl;
    return s;
}
