/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Health component
*/

#include "HealthComponent.hpp"

HealthComponent::HealthComponent(int health):
    _type(ComponentHealth), _health(health)
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::setHealth(int health)
{
    this->_health = health;
}

int HealthComponent::getHealth() const
{
    return (this->_health);
}

ComponentType HealthComponent::getType() const
{
    return (_type);
}

std::string HealthComponent::getOutput() const
{
    std::string output("Health Component (health: " + std::to_string(this->_health)  + ")");
    return (output);
}
