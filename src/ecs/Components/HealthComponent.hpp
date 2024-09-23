/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Health component 
*/

#ifndef HEALTHCOMPONENT_HPP_
#define HEALTHCOMPONENT_HPP_

#include "../IComponent.hpp"

class HealthComponent: public IComponent {
    public:
        HealthComponent(int health);
        ~HealthComponent();
        void setHealth(int health);
        int getHealth() const;
        ComponentType getType() const;
        std::string getOutput() const;
    protected:
        ComponentType _type;
    private:
        int _health;
};

#endif /* !HEALTHCOMPONENT_HPP_ */
