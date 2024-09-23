/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position 
*/

#include "PositionComponent.hpp"
#include <iostream>

PositionComponent::PositionComponent(int x, int y):
    _type(ComponentPosition), _x(x), _y(y)
{
}

PositionComponent::~PositionComponent()
{
}

void PositionComponent::setPositions(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

void PositionComponent::setX(int x)
{
    this->_x = x;
}

void PositionComponent::setY(int y)
{
    this->_y = y;
}

int PositionComponent::getPositionX() const
{
    return (this->_x);
}

int PositionComponent::getPositionY() const
{
    return (this->_y);
}

ComponentType PositionComponent::getType() const
{
    return(_type);
}


std::string PositionComponent::getOutput() const
{
    std::string output("Position Component (x: " + std::to_string(this->_x) + ", y: " + std::to_string(this->_y) + ")");
    return (output);
}
