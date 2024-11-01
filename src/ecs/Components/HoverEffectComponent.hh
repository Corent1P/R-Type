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

    /**
     * @brief HoverEffectComponent class to handle hover state of an entity.
     */
    class HoverEffectComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new HoverEffectComponent object.
             */
            HoverEffectComponent();

            /**
             * @brief Destroy the HoverEffectComponent object.
             */
            ~HoverEffectComponent();

            /**
             * @brief Set the hover state of the component.
             *
             * @param isHovered Boolean indicating if the component is hovered.
             */
            void setHoverState(bool isHovered);

            /**
             * @brief Get the hover state of the component.
             *
             * @return true if the component is hovered, false otherwise.
             */
            bool getHoverState() const;

            /**
             * @brief Get the output string of the component.
             *
             * @return std::string representing the output.
             */
            std::string getOutput() const;

        private:
            /**
             * @brief Boolean indicating if the component is hovered.
             */
            bool _isHovered;
    };
}
