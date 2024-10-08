/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Scale component
*/

#ifndef SCALECOMPONENT_HPP_
#define SCALECOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include "../IComponent.hh"

namespace RType {

    class ScaleComponent: public RType::IComponent {
        public:
            ScaleComponent(float x, float y);
            ~ScaleComponent() = default;

            void setScale(float x, float y);
            float getScaleX() const;
            float getScaleY() const;
            std::string getOutput() const;
        private:
            float _scaleX;
            float _scaleY;
    };
}

#endif /* !SCALECOMPONENT_HPP_ */
