/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Component related to the entity position 
*/

#include "PositionComponent.hpp"
#include <iostream>

PositionComponent::PositionComponent(int x, int y)
{
    setType();
    this->setPositions(x, y);
}

PositionComponent::~PositionComponent()
{
}

void PositionComponent::setPositions(int x, int y) {
    this->_x = x;
    this->_y = y;
}

int PositionComponent::getPositionX()
{
    return (this->_x);
}

int PositionComponent::getPositionY()
{
    return (this->_y);
}

void PositionComponent::setType() {
    this->_type = ComponentPosition;
}

ComponentType PositionComponent::getType() const
{
    return(_type);
}