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

    class ShootIntervalComponent: public RType::IComponent {
        public:
            ShootIntervalComponent(float shootInterval);
            ~ShootIntervalComponent();
            void setShootInterval(float shootInterval);
            float getShootInterval() const;
            std::string getOutput() const;
        private:
            float _shootInterval;
    };
}

#endif /* !SHOOTINTERVALCOMPONENT_HPP_ */