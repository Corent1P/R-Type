/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ClickEffect component
*/

#pragma once

#include "../IComponent.hh"
#include <functional>
#include "../Entity.hpp"

namespace RType {
    /**
     * @brief ClickEffectComponent class for handling the click effect of a button
     *
     */
    class ClickEffectComponent: public RType::IComponent {
        public:

            /**
             * @brief Construct a new Click Effect Component object
             *
             * @param clickEffect The effect to apply
             */
            ClickEffectComponent(std::function<void(std::shared_ptr<Entity>)> clickEffect);

            /**
             * @brief Destroy the Click Effect Component object
             *
             */
            ~ClickEffectComponent();

            /**
             * @brief Set the click effect
             *
             * @param clickEffect The effect to apply
             */
            void setClickEffect(std::function<void(std::shared_ptr<Entity>)> clickEffect);

            /**
             * @brief Get the click effect
             *
             * @return std::function<void(std::shared_ptr<RType::Entity>)> The click effect
             */
            std::function<void(std::shared_ptr<RType::Entity>)> getClickEffect() const;

            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;

        private:

            /**
             * @brief The effect to apply on click
             *
             */
            std::function<void(std::shared_ptr<Entity>)> _clickEffect;
    };
}
