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

    class VelocityComponent: public RType::IComponent {
        public:
            VelocityComponent(int velocity);
            ~VelocityComponent();
            void setVelocity(int velocity);
            int getVelocity() const;
            std::string getOutput() const;
        private:
            int _velocity;
    };
}

#endif /* !VELOCITYCOMPONENT_HPP_ */
