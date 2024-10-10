/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Scale methods
*/

#include "ScaleComponent.hh"

RType::ScaleComponent::ScaleComponent(float x, float y):
    _scaleX(x), _scaleY(y)
{
}

void RType::ScaleComponent::setScale(float x, float y)
{
   _scaleX = x;
   _scaleY = y;
}

float RType::ScaleComponent::getScaleX() const
{
    return _scaleX;
}

float RType::ScaleComponent::getScaleY() const
{
    return _scaleY;
}

sf::Vector2f RType::ScaleComponent::getScales() const
{
	return {_scaleX, _scaleY};
}

std::string RType::ScaleComponent::getOutput() const
{
    std::string output("Scale Component ("")");
    return (output);
}

