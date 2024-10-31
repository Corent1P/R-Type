/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AutoUpdateTextComponent
*/

#include "AutoUpdateTextComponent.hh"

RType::AutoUpdateTextComponent::AutoUpdateTextComponent(enum autoUpdateWithValue value):
    _value(value)
{
}

enum RType::autoUpdateWithValue RType::AutoUpdateTextComponent::getValue() const
{
    return _value;
}

std::string RType::AutoUpdateTextComponent::getOutput() const
{
    std::string output("AutoUpdateTextComponent");
    return output;
}
