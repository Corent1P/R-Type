/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Health component
*/

#include "HealthComponent.hpp"

HealthComponent::HealthComponent(int health)
{
    setType();
    setHealth(health);
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::setHealth(int health)
{
    this->_heath = health;
}

int HealthComponent::getHealth()
{
    return(this->_heath);
}

void HealthComponent::setType() {
    this->_type = ComponentHealth;
}

ComponentType HealthComponent::getType() const
{
    return(_type);
}