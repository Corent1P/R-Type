/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Entity file
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "IComponent.hpp"

class Entity {
    public:
        Entity(uint16_t id);
        ~Entity() = default;

        std::vector<std::shared_ptr<IComponent>> getComponents(void) const;
        uint16_t getId(void) const;

        template <typename T>
        std::shared_ptr<T> pushComponent(std::shared_ptr<T> component) {
            this->_components.push_back(component);
            return component;
        }

        template <typename T>
        std::shared_ptr<T> getComponent() const {
            for (const auto& component : _components) {
                std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
                if (castedComponent) {
                    return castedComponent;
                }
            }
            return nullptr;
        }

    private:
        std::vector<std::shared_ptr<IComponent>> _components;
        uint16_t _id;
};

// std::ostream &operator<<(std::ostream &s, const Entity &entity);

#endif /* !ENTITY_HPP_ */
