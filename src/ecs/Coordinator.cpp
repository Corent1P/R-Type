/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ECS Coordinator for Components & systems
*/

#include "Coordinator.hh"

RType::Coordinator::Coordinator():
    _idEntities(0)
{
}

std::shared_ptr<RType::Entity> RType::Coordinator::generateNewEntity() {
    std::shared_ptr<Entity> newEntity = std::make_unique<Entity>(_idEntities++);
    _entities.push_back(newEntity);
    return (newEntity);
}

void RType::Coordinator::generateNewSystem(std::shared_ptr<ISystem> sys) {
    _systems.push_back(sys);
}

std::vector<std::shared_ptr<RType::Entity>> RType::Coordinator::getEntities() const
{
    return _entities;
}

std::vector<std::shared_ptr<RType::ISystem>> RType::Coordinator::getSystems() const
{
    return _systems;
}

std::ostream &operator<<(std::ostream &s, const RType::Coordinator &coordinator)
{
	std::vector<std::shared_ptr<RType::Entity>> entities = coordinator.getEntities();
	std::vector<std::shared_ptr<RType::ISystem>> systems = coordinator.getSystems();

    s << "Coordinator:\n";
    for (auto entity: entities)
        s << "\t" << *entity;
    for (auto system: systems)
        s << "\t" << *system;
    return s;
}