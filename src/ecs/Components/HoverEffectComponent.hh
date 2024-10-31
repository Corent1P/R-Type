/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** HoverEffect component
*/

#pragma once

#include "../IComponent.hh"
#include <functional>
#include "../Entity.hpp"

namespace RType {

    class HoverEffectComponent: public RType::IComponent {
        public:
            HoverEffectComponent();
            ~HoverEffectComponent();
            void setHoverState(bool isHovered);
            bool getHoverState() const;
            std::string getOutput() const;
        private:
            bool _isHovered;
    };
}
