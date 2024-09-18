/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Abrastraction for Components
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"

class AComponent: public IComponent {
    public:
        AComponent();
        ~AComponent() = default;
        ComponentType getType() const;
    protected:
        ComponentType _type;
};

std::ostream &operator<<(std::ostream &s, const IComponent &component);

#endif /* !ACOMPONENT_HPP_ */
