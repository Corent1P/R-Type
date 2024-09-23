/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Entity methods
*/

#include "Entity.hpp"

Entity::Entity(uint16_t id):
    _id(id)
{
}

std::vector<std::shared_ptr<IComponent>> Entity::getComponents(void) const
{
	return _components;
}

uint16_t Entity::getId(void) const
{
	return _id;
}

std::ostream &operator<<(std::ostream &s, const Entity &entity)
{
	std::vector<std::shared_ptr<IComponent>> components = entity.getComponents();

    s << "Entity[" << entity.getId() << "]:\n";

    for (auto component: components) {
        s << "\t\t" << *component << std::endl;
    }

    return s;
}
