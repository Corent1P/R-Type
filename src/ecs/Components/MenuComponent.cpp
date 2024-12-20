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

bool RType::MenuComponent::operator==(const MenuComponent &other) const
{
	return _menu == other.getMenu() || _menu == EVERYWHERE || other.getMenu() == EVERYWHERE;
}

std::string RType::MenuComponent::getOutput() const
{
    std::string output("Menu Component (menu: " + std::to_string(_menu) + ")");
    return (output);
}
