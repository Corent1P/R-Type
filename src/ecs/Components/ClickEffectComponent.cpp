/*
** EPITECH PROJECT, 2024
** rType
** File description:
** ClickEffectComponent
*/

#include "ClickEffectComponent.hh"

RType::ClickEffectComponent::ClickEffectComponent(std::function<void(std::shared_ptr<Entity>)> clickEffect):
	_clickEffect(clickEffect)
{
}

RType::ClickEffectComponent::~ClickEffectComponent()
{
}

void RType::ClickEffectComponent::setClickEffect(std::function<void(std::shared_ptr<Entity>)> clickEffect)
{
	_clickEffect = clickEffect;
}

std::function<void(std::shared_ptr<RType::Entity>)> RType::ClickEffectComponent::getClickEffect() const
{
	return _clickEffect;
}

std::string RType::ClickEffectComponent::getOutput() const
{
    std::string output("ClickEffect Component");
    return (output);
}
