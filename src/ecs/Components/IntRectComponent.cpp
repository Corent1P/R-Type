/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Scale methods
*/

#include "IntRectComponent.hh"

RType::IntRectComponent::IntRectComponent(int left, int top, int width, int height):
    _left(left), _top(top), _width(width), _height(height)
{
}

void RType::IntRectComponent::setIntRect(int left, int top, int width, int height)
{
   _left = left;
   _top = top;
   _width = width;
   _height = height;
}

int RType::IntRectComponent::getIntRectLeft() const
{
    return _left;
}

int RType::IntRectComponent::getIntRectTop() const
{
    return _top;
}

int RType::IntRectComponent::getIntRectWidth() const
{
    return _width;
}

int RType::IntRectComponent::getIntRectHeight() const
{
    return _height;
}

std::string RType::IntRectComponent::getOutput() const
{
    std::string output("IntRect Component ("")");
    return (output);
}
