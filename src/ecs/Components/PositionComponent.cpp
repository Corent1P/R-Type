/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position 
*/

#include "PositionComponent.hpp"
#include <iostream>

RType::PositionComponent::PositionComponent(int x, int y):
   _x(x), _y(y)
{
}

RType::PositionComponent::~PositionComponent()
{
}

void RType::PositionComponent::setPositions(int x, int y)
{
    _x = x;
    _y = y;
}

void RType::PositionComponent::setX(int x)
{
    _x = x;
}

void RType::PositionComponent::setY(int y)
{
    _y = y;
}

int RType::PositionComponent::getPositionX() const
{
    return (_x);
}

int RType::PositionComponent::getPositionY() const
{
    return (_y);
}

std::string RType::PositionComponent::getOutput() const
{
    std::string output("Position Component (x: " + std::to_string(_x) + ", y: " + std::to_string(_y) + ")");
    return (output);
}
