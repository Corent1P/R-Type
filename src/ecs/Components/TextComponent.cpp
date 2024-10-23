/*
** EPITECH PROJECT, 2024
** rType
** File description:
** TextComponent
*/

#include "TextComponent.hh"

RType::TextComponent::TextComponent(std::string text, std::size_t fontSize, std::shared_ptr<sf::Font> font)
{
    _text = std::make_shared<sf::Text>();
	_text->setFont(*font);
	setText(text, fontSize);
}

RType::TextComponent::~TextComponent()
{
}

void RType::TextComponent::setTextWithoutVariable(std::string text)
{
	_textWithoutVariable = text;
}


void RType::TextComponent::setText(std::string text, std::size_t fontSize)
{
	_text->setString(text);
	_text->setCharacterSize(fontSize);
	_text->setFillColor(sf::Color::Red);
}

std::shared_ptr<sf::Text> RType::TextComponent::getText() const
{
	return _text;
}

std::string RType::TextComponent::getOutput() const
{
    std::string output("Text Component (text: " + _text->getString() + ")");
    return (output);
}

const std::string& RType::TextComponent::getTextWithoutVariable() const
{
	return _textWithoutVariable;
}