/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Entity file
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include "IComponent.hpp"
#include <typeinfo>

class Entity {
    public:
        Entity(uint16_t id);
        ~Entity() = default;
        
        template <typename T>
        std::shared_ptr<T> pushComponent(std::shared_ptr<T> component) {
            this->_components.push_back(component);
            return component;
        }

        template <typename T>
        std::shared_ptr<T> getComponent() {
            for (const auto& component : _components) {
                if (typeid(*component) == typeid(T)) {
                    return std::dynamic_pointer_cast<T>(component);
                }
            }
            return nullptr;
        }

    private:
        std::vector<std::shared_ptr<IComponent>> _components;
        uint16_t _id;
};

#endif /* !ENTITY_HPP_ */
