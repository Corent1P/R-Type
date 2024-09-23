/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Health component
*/

#include "HealthComponent.hh"

RType::HealthComponent::HealthComponent(int health):
    _health(health)
{
}

RType::HealthComponent::~HealthComponent()
{
}

void RType::HealthComponent::setHealth(int health)
{
    _health = health;
}

int RType::HealthComponent::getHealth() const
{
    return (_health);
}

std::string RType::HealthComponent::getOutput() const
{
    std::string output("Health Component (health: " + std::to_string(_health)  + ")");
    return (output);
}
