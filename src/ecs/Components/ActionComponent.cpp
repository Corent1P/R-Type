/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Action Component methods
*/

#include "ActionComponent.hh"

RType::ActionComponent::ActionComponent()
{
    _action = RType::NOTHING;

    _actions.push_back(true);
    _actions.push_back(false);
}

RType::ActionComponent::ActionComponent(Action action)
{
    _action = action;
    _actions.push_back(true);
    _actions.push_back(false);
}


RType::ActionComponent::~ActionComponent()
{
}

void RType::ActionComponent::setAction(Action action)
{
    _action = action;
}

RType::Action RType::ActionComponent::getAction() const
{
    return (_action);
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
    std::string action("");
    switch (_action)
        {
        case NOTHING:
            action = "NOTHING";
            break;
        case SHOOTING:
            action = "SHOOTING";
            break;
        default:
            action = "NOTHING";
            break;
        }
    std::string output("Entity Action Component (entity Action " + action + ")");
    return output;
}
