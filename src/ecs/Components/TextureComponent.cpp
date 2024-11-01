/*
** EPITECH PROJECT, 2024
** rType
** File description:
** TextureComponent
*/

#include "TextureComponent.hh"

RType::TextureComponent::TextureComponent(std::string path):
    _texture(std::make_shared<sf::Texture>())
{
    setTexture(path);
}

void RType::TextureComponent::setTexture(std::string path)
{
    if (!_texture->loadFromFile(path)) {
        return;
    }
    _path = path;
}

std::shared_ptr<sf::Texture> RType::TextureComponent::getTexture() const
{
    return _texture;
}

std::string RType::TextureComponent::getPath() const
{
	return _path;
}

std::string RType::TextureComponent::getOutput() const
{
    std::string output("Texture Component (path: " + _path + ", width: " + std::to_string(_texture->getSize().x)  + ", height: " + std::to_string(_texture->getSize().y)+ ")");
    return (output);
}
