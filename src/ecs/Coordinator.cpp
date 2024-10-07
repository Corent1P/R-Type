/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ECS Coordinator for Components & systems
*/

#include "Coordinator.hh"

RType::Coordinator::Coordinator():
    _mtx(std::make_shared<std::mutex>()), _idEntities(0)
{
}

std::shared_ptr<RType::Entity> RType::Coordinator::generateNewEntity(uint16_t serverId) {
    std::unique_lock<std::mutex> lock(*_mtx);

    std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(_idEntities++, _mtx, serverId);
    _entities.push_back(newEntity);
    return (newEntity);
}

void RType::Coordinator::generateNewSystem(std::shared_ptr<ISystem> sys) {
    std::unique_lock<std::mutex> lock(*_mtx);
    _systems.push_back(sys);
}

const std::vector<std::shared_ptr<RType::Entity>> &RType::Coordinator::getEntities() const
{
    std::unique_lock<std::mutex> lock(*_mtx);
    return _entities;
}

const std::vector<std::shared_ptr<RType::ISystem>> &RType::Coordinator::getSystems() const
{
    std::unique_lock<std::mutex> lock(*_mtx);
    return _systems;
}

std::shared_ptr<RType::Entity> RType::Coordinator::addEntity(void)
{
    std::unique_lock<std::mutex> lock(*_mtx);
    return generateNewEntity(-1);
}

void RType::Coordinator::deleteEntity(std::shared_ptr<Entity> entityToDestroy)
{
    std::cout << "delete: " << entityToDestroy->getId() << std::endl;
    std::unique_lock<std::mutex> lock(*_mtx);
    // entityToDestroy->clearComponents();
    auto it = std::find(_entities.begin(), _entities.end(), entityToDestroy);
    if (it != _entities.end()) {
        _entities.erase(it);
    }
}

std::ostream &operator<<(std::ostream &s, const RType::Coordinator &coordinator)
{
	std::vector<std::shared_ptr<RType::Entity>> entities = coordinator.getEntities();
	std::vector<std::shared_ptr<RType::ISystem>> systems = coordinator.getSystems();

    s << "Coordinator:\n";
    for (auto entity: entities)
        s << "\t" << *entity;
    for (auto system: systems)
        s << "\t" << *system << std::endl;
    return s;
}
