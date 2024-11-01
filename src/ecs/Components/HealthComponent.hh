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

    /**
     * @brief HealthComponent class for handling the health of an entity
     *
     */
    class HealthComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Health Component object
             *
             * @param health The health to set
             */
            HealthComponent(int health);

            /**
             * @brief Destroy the Health Component object
             *
             */
            ~HealthComponent();

            /**
             * @brief Set the health
             *
             * @param health The health to set
             */
            void setHealth(int health);

            /**
             * @brief Get the health
             *
             * @return int The health
             */
            int getHealth() const;

            /**
             * @brief Get the Max Health object
             *
             * @return int
             */
            int getMaxHealth() const;

            /**
             * @brief Set the isDead
             *
             * @param isDead The isDead to set
             */
            void setIsDead(bool isDead);

            /**
             * @brief Get the isDead
             *
             * @return bool The isDead
             */
            bool getIsDead() const;


            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;
        private:

            /**
             * @brief The health
             *
             */
            int _health;

            /**
             * @brief The max health
             *
             */
            int _maxHealth;

            /**
             * @brief The isDead
             *
             */
            bool _isDead;
    };
}

#endif /* !HEALTHCOMPONENT_HPP_ */
