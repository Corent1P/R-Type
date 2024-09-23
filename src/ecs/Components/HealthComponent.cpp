/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Health component
*/

#include "HealthComponent.hpp"

RType::HealthComponent::HealthComponent(int health):
    _type(ComponentHealth), _health(health)
{
}

RType::HealthComponent::~HealthComponent()
{
}

void RType::HealthComponent::setHealth(int health)
{
    this->_health = health;
}

int RType::HealthComponent::getHealth() const
{
    return (this->_health);
}

RType::ComponentType RType::HealthComponent::getType() const
{
    return (_type);
}

std::string RType::HealthComponent::getOutput() const
{
    std::string output("Health Component (health: " + std::to_string(this->_health)  + ")");
    return (output);
}
