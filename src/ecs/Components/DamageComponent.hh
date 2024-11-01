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

    /**
     * @brief DamageComponent class for handling the damage of an entity
     *
     */
    class DamageComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Damage Component object
             *
             * @param damage The damage to set
             */
            DamageComponent(int damage);

            /**
             * @brief Destroy the Damage Component object
             *
             */
            ~DamageComponent();

            /**
             * @brief Set the damage
             *
             * @param damage The damage to set
             */
            void setDamage(int damage);

            /**
             * @brief Get the damage
             *
             * @return int The damage
             */
            int getDamage() const;

            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;
        private:

            /**
             * @brief The damage
             *
             */
            int _damage;
    };
}

#endif /* !DAMAGECOMPONENT_HPP_ */
