/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFML window component methods
*/

#include "SFWindowComponent.hh"

SFWindowComponent::SFWindowComponent(int screenWidth, int screenHeight)
{
    setRenderWindow(screenWidth, screenHeight);
}

SFWindowComponent::~SFWindowComponent()
{
}

void SFWindowComponent::setRenderWindow(int screenWidth, int screenHeight)
{
    _window = std::make_shared<sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "SFML window")>;
}

sf::RenderWindow SFWindowComponent::getWindow() const 
{

}