/*
** EPITECH PROJECT, 2024
** rType
** File description:
** AComponent
*/

#include "AComponent.hpp"

AComponent::AComponent():
    _type(ComponentBasic)
{
}

ComponentType AComponent::getType() const
{
	return _type;
}
