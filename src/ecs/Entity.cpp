/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Entity methods
*/

#include "Entity.hpp"

RType::Entity::Entity(uint16_t id, std::shared_ptr<std::mutex> mtx, int serverId):
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
	return _id;
}

void RType::Entity::setServerId(int serverId)
{
    std::unique_lock<std::mutex> lock(*_mtx);
	_serverId = serverId;
}

int RType::Entity::getServerId(void) const
{
    std::unique_lock<std::mutex> lock(*_mtx);
	return _serverId;
}

void RType::Entity::clearComponents()
{
    _components.clear();
}

bool RType::Entity::operator<(const RType::Entity &other) const
{
	return _id < other.getId();
}

bool RType::Entity::operator==(const RType::Entity &other) const
{
	return _id == other.getId();
}

RType::Entity &RType::Entity::operator=(const RType::Entity &other)
{
    if (this == &other)
        return *this;
    _components = other._components;
    _id = other._id;
    _serverId = other._serverId;

    _mtx = std::make_shared<std::mutex>();

    return *this;
}

std::ostream &operator<<(std::ostream &s, const RType::Entity &entity)
{
	std::vector<std::shared_ptr<RType::IComponent>> components = entity.getComponents();

    s << "Entity[" << entity.getId() << "]";
    if (entity.getServerId() >= 0) {
        s << "[" << entity.getServerId() << "]:" << std::endl;
    } else
        s << ":" << std::endl;
    for (auto component: components) {
        s << "\t\t" << component->getOutput() << std::endl;
    }

    return s;
}

bool RType::Entity::compareEntity(const std::shared_ptr<RType::Entity> &entity1, const std::shared_ptr<RType::Entity> &entity2)
{
    return entity1->getId() < entity2->getId();
}
