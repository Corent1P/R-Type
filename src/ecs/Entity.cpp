/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Entity methods
*/

#include "Entity.hpp"

RType::Entity::Entity(uint16_t id, std::shared_ptr<std::mutex> mtx, uint16_t serverId):
    _id(id), _mtx(mtx), _serverId(serverId)
{
}

std::vector<std::shared_ptr<RType::IComponent>> RType::Entity::getComponents(void) const
{
    std::unique_lock<std::mutex> lock(*_mtx);
	return _components;
}

uint16_t RType::Entity::getId(void) const
{
    std::unique_lock<std::mutex> lock(*_mtx);
	return _id;
}

void RType::Entity::setServerId(uint16_t serverId)
{
    std::unique_lock<std::mutex> lock(*_mtx);
	_serverId = serverId;
}

uint16_t RType::Entity::getServerId(void) const
{
    std::unique_lock<std::mutex> lock(*_mtx);
	return _serverId;
}

void RType::Entity::clearComponents()
{
    _components.clear();
}

std::ostream &operator<<(std::ostream &s, const RType::Entity &entity)
{
	std::vector<std::shared_ptr<RType::IComponent>> components = entity.getComponents();

    s << "Entity[" << entity.getId() << "]:" << std::endl;

    for (auto component: components) {
        s << "\t\t" << component->getOutput() << std::endl;
    }

    return s;
}
