/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Velocity component
*/

#include "VelocityComponent.hh"

RType::VelocityComponent::VelocityComponent(int velocity):
    _velocity(velocity)
{
}

RType::VelocityComponent::~VelocityComponent()
{
}

void RType::VelocityComponent::setVelocity(int velocity)
{
    _velocity = velocity;
}

int RType::VelocityComponent::getVelocity() const
{
    return (_velocity);
}

std::string RType::VelocityComponent::getOutput() const
{
    std::string output("Velocity Component (velocity: " + std::to_string(_velocity)  + ")");
    return (output);
}
