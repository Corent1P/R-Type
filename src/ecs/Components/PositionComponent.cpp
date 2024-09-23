/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position 
*/

#include "PositionComponent.hpp"
#include <iostream>

RType::PositionComponent::PositionComponent(int x, int y):
    _type(ComponentPosition), _x(x), _y(y)
{
}

RType::PositionComponent::~PositionComponent()
{
}

void RType::PositionComponent::setPositions(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

void RType::PositionComponent::setX(int x)
{
    this->_x = x;
}

void RType::PositionComponent::setY(int y)
{
    this->_y = y;
}

int RType::PositionComponent::getPositionX() const
{
    return (this->_x);
}

int RType::PositionComponent::getPositionY() const
{
    return (this->_y);
}

RType::ComponentType RType::PositionComponent::getType() const
{
    return(_type);
}


std::string RType::PositionComponent::getOutput() const
{
    std::string output("Position Component (x: " + std::to_string(this->_x) + ", y: " + std::to_string(this->_y) + ")");
    return (output);
}
