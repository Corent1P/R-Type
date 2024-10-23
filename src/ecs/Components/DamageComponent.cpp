/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Damage component
*/

#include "DamageComponent.hh"

RType::DamageComponent::DamageComponent(int damage):
    _damage(damage)
{
}

RType::DamageComponent::~DamageComponent()
{
}

void RType::DamageComponent::setDamage(int damage)
{
    _damage = damage;
}

int RType::DamageComponent::getDamage() const
{
    return (_damage);
}

std::string RType::DamageComponent::getOutput() const
{
    std::string output("Damage Component (damage: " + std::to_string(_damage)  + ")");
    return (output);
}
