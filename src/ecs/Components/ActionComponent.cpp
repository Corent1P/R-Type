/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Action Component methods
*/

#include "ActionComponent.hh"

RType::ActionComponent::ActionComponent()
{
    _actions.push_back(true);
    _actions.push_back(false);
    _actions.push_back(false);
}

RType::ActionComponent::~ActionComponent()
{
}

void RType::ActionComponent::setActions(Action action, bool newBool) {
    _actions.at(action) = newBool;
}

bool RType::ActionComponent::getActions(Action action) const
{
    return (_actions.at(action));
}

std::string RType::ActionComponent::getOutput() const
{
    std::string output("Entity Action Component (entity Action)");
    return output;
}
