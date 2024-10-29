/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Damage component 
*/

#ifndef DAMAGECOMPONENT_HPP_
#define DAMAGECOMPONENT_HPP_

#include "../IComponent.hh"
namespace RType {

    class DamageComponent: public RType::IComponent {
        public:
            DamageComponent(int damage);
            ~DamageComponent();
            void setDamage(int damage);
            int getDamage() const;
            std::string getOutput() const;
        private:
            int _damage;
    };
}

#endif /* !DAMAGECOMPONENT_HPP_ */
