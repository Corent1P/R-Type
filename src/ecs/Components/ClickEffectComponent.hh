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

    class ClickEffectComponent: public RType::IComponent {
        public:
            ClickEffectComponent(std::function<void(std::shared_ptr<Entity>)> clickEffect);
            ~ClickEffectComponent();
            void setClickEffect(std::function<void(std::shared_ptr<Entity>)> clickEffect);
            std::function<void(std::shared_ptr<RType::Entity>)> getClickEffect() const;
            std::string getOutput() const;
        private:
            std::function<void(std::shared_ptr<Entity>)> _clickEffect;
    };
}
