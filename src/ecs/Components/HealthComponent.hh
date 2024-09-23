/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Health component 
*/

#ifndef HEALTHCOMPONENT_HPP_
#define HEALTHCOMPONENT_HPP_

#include "../IComponent.hh"
namespace RType {

    class HealthComponent: public RType::IComponent {
        public:
            HealthComponent(int health);
            ~HealthComponent();
            void setHealth(int health);
            int getHealth() const;
            std::string getOutput() const;
        private:
            int _health;
    };
}

#endif /* !HEALTHCOMPONENT_HPP_ */
