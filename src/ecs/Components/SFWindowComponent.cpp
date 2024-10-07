/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFML window component methods
*/

#include "SFWindowComponent.hh"

RType::SFWindowComponent::SFWindowComponent(int screenWidth, int screenHeight):
    _window(std::make_shared<sf::RenderWindow>(sf::VideoMode(screenWidth, screenHeight), "SFML window"))
{
}

RType::SFWindowComponent::~SFWindowComponent()
{
    _window->close();
}

std::shared_ptr<sf::RenderWindow> RType::SFWindowComponent::getWindow() const
{
    return _window;
}

std::string RType::SFWindowComponent::getOutput() const
{
    std::string output("SF Window Component (width: " + std::to_string(_window->getSize().x)  + ", height: " + std::to_string(_window->getSize().y)+ ")");
    return (output);
}

bool RType::SFWindowComponent::getIsOpen()
{
    return _window->isOpen();
}
