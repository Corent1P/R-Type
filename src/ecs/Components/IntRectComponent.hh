/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** IntRect component
*/

#ifndef INTRECTCOMPONENT_HPP_
#define INTRECTCOMPONENT_HPP_

#include <SFML/Graphics.hpp>
#include "../IComponent.hh"

namespace RType {

    class IntRectComponent: public RType::IComponent {
        public:
            IntRectComponent(int left, int top, int width, int height);
            ~IntRectComponent() = default;

            void setIntRect(int left, int top, int width, int height);
            int getIntRectLeft() const;
            int getIntRectTop() const;
            int getIntRectWidth() const;
            int getIntRectHeight() const;
            std::string getOutput() const;
        private:
            int _left;
            int _top;
            int _width;
            int _height;
    };
}

#endif /* !INTRECTCOMPONENT_HPP_ */
