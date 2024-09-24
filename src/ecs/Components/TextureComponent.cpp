/*
** EPITECH PROJECT, 2024
** rType
** File description:
** TextureComponent
*/

#include "TextureComponent.hh"

RType::TextureComponent::TextureComponent(std::string path)
{
    setTexture(path);
}

RType::TextureComponent::~TextureComponent()
{
}

void RType::TextureComponent::setTexture(std::string path)
{
    if (!_texture.loadFromFile(path)) {
        throw Error ("Failed Load Texture");
	}
	_path = path;
}

sf::Texture RType::TextureComponent::getTexture() const
{
	return _texture;
}

std::string RType::TextureComponent::getPath() const
{
	return _path;
}

std::string RType::TextureComponent::getOutput() const
{
    std::string output("Texture Component (path: " + _path + ", width: " + std::to_string(_texture.getSize().x)  + ", height: " + std::to_string(_texture.getSize().y)+ ")");
    return (output);
}
