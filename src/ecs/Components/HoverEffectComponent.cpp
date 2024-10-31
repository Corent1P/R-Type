/*
** EPITECH PROJECT, 2024
** rType
** File description:
** HoverEffectComponent
*/

#include "HoverEffectComponent.hh"

RType::HoverEffectComponent::HoverEffectComponent():
    _isHovered(false)
{}

RType::HoverEffectComponent::~HoverEffectComponent()
{}

void RType::HoverEffectComponent::setHoverState(bool isHovered)
{
    _isHovered = isHovered;
}

bool RType::HoverEffectComponent::getHoverState() const
{
    return _isHovered;
}

std::string RType::HoverEffectComponent::getOutput() const
{
    std::string output("HoverEffect Component");
    return (output);
}
