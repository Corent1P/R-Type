/*
** EPITECH PROJECT, 2024
** rType
** File description:
** MenuComponent
*/

#include "MenuComponent.hh"

RType::MenuComponent::MenuComponent(Menu menu):
	_menu(menu)
{
}

RType::MenuComponent::~MenuComponent()
{
}

void RType::MenuComponent::setMenu(Menu menu)
{
	_menu = menu;
}

RType::Menu RType::MenuComponent::getMenu() const
{
	return _menu;
}

std::string RType::MenuComponent::getOutput() const
{
    std::string output("Menu Component (menu: " + std::to_string(_menu) + ")");
    return (output);
}
