/*
** EPITECH PROJECT, 2024
** rType
** File description:
** SpriteComponent
*/

#include "SpriteComponent.hh"

RType::SpriteComponent::SpriteComponent(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos)
{
    _sprite = std::make_shared<sf::Sprite>();
    setSprite(texture, pos);
}

RType::SpriteComponent::SpriteComponent(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale)
{
    _sprite = std::make_shared<sf::Sprite>();
    setSprite(texture, pos, scale);
}

RType::SpriteComponent::SpriteComponent(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale, sf::IntRect rect)
{
    _sprite = std::make_shared<sf::Sprite>();
    setSprite(texture, pos, scale, rect);
}

void RType::SpriteComponent::setSprite(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos)
{
    _sprite->setTexture(*(texture));
    _sprite->setPosition(pos);
    _sprite->setScale(sf::Vector2f (2, 2));
}

void RType::SpriteComponent::setSprite(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale)
{
    _sprite->setTexture(*(texture));
    _sprite->setPosition(pos);
    _sprite->setScale(scale);
}

void RType::SpriteComponent::setSprite(std::shared_ptr<sf::Texture> texture, sf::Vector2f pos, sf::Vector2f scale, sf::IntRect rect)
{
    _sprite->setTexture(*(texture));
    _sprite->setPosition(pos);
    _sprite->setScale(scale);
    _sprite->setTextureRect(rect);
}

std::shared_ptr<sf::Sprite> RType::SpriteComponent::getSprite() const
{
	return _sprite;
}

std::string RType::SpriteComponent::getOutput() const
{
    std::string output("Sprite Component");
    return (output);
}
