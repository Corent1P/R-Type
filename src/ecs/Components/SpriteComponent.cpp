/*
** EPITECH PROJECT, 2024
** rType
** File description:
** SpriteComponent
*/

#include "SpriteComponent.hh"

RType::SpriteComponent::SpriteComponent(sf::Texture texture, sf::Vector2f pos)
{
    setSprite(texture, pos);
}

RType::SpriteComponent::SpriteComponent(sf::Texture texture, sf::Vector2f pos, sf::Vector2f scale)
{
    setSprite(texture, pos, scale);
}

void RType::SpriteComponent::setSprite(sf::Texture texture, sf::Vector2f pos)
{
    _sprite.setTexture(texture);
    _sprite.setPosition(pos);
}

void RType::SpriteComponent::setSprite(sf::Texture texture, sf::Vector2f pos, sf::Vector2f scale)
{
    _sprite.setTexture(texture);
    _sprite.setPosition(pos);
    _sprite.setScale(scale);
}

sf::Sprite RType::SpriteComponent::getSprite() const
{
	return _sprite;
}

void RType::SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

std::string RType::SpriteComponent::getOutput() const
{
    std::string output("Sprite Component");
    return (output);
}
