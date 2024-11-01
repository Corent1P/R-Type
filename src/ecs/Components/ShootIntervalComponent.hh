/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ShootInterval component
*/

#ifndef SHOOTINTERVALCOMPONENT_HPP_
#define SHOOTINTERVALCOMPONENT_HPP_

#include "../IComponent.hh"
namespace RType {

    /**
     * @brief Shoot interval component class
     */
    class ShootIntervalComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new ShootIntervalComponent object
             *
             * @param shootInterval Shoot interval duration
             */
            ShootIntervalComponent(float shootInterval);

            /**
             * @brief Destroy the ShootIntervalComponent object
             */
            ~ShootIntervalComponent();

            /**
             * @brief Set the shoot interval
             *
             * @param shootInterval Shoot interval duration
             */
            void setShootInterval(float shootInterval);

            /**
             * @brief Get the shoot interval
             *
             * @return float Shoot interval duration
             */
            float getShootInterval() const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Shoot interval duration
             */
            float _shootInterval;
    };
}

#endif /* !SHOOTINTERVALCOMPONENT_HPP_ */