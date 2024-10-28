/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ShootInterval component
*/

#include "ShootIntervalComponent.hh"

RType::ShootIntervalComponent::ShootIntervalComponent(float shootInterval):
    _shootInterval(shootInterval)
{
}

RType::ShootIntervalComponent::~ShootIntervalComponent()
{
}

void RType::ShootIntervalComponent::setShootInterval(float shootInterval)
{
    _shootInterval = shootInterval;
}

float RType::ShootIntervalComponent::getShootInterval() const
{
    return (_shootInterval);
}

std::string RType::ShootIntervalComponent::getOutput() const
{
    std::string output("ShootInterval Component (shootInterval: " + std::to_string(_shootInterval)  + ")");
    return (output);
}
