/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Velocity component
*/

#ifndef VELOCITYCOMPONENT_HPP_
#define VELOCITYCOMPONENT_HPP_

#include "../IComponent.hh"
namespace RType {

    /**
     * @brief Velocity component class
     */
    class VelocityComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new VelocityComponent object
             *
             * @param velocity Initial velocity
             */
            VelocityComponent(int velocity);

            /**
             * @brief Destroy the VelocityComponent object
             */
            ~VelocityComponent();

            /**
             * @brief Set the velocity
             *
             * @param velocity New velocity
             */
            void setVelocity(int velocity);

            /**
             * @brief Get the velocity
             *
             * @return int Current velocity
             */
            int getVelocity() const;

            /**
             * @brief Get the output as a string
             *
             * @return std::string Output string
             */
            std::string getOutput() const;
        private:
            /**
             * @brief Current velocity
             */
            int _velocity;
    };
}

#endif /* !VELOCITYCOMPONENT_HPP_ */
