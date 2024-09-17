/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Entity file
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <iostream>
#include "vector"
#include "IComponent.hpp"
#include <typeInfo>

class Entity {
    public:
        Entity();
        ~Entity();
        
        template <typename T>
        T* pushComponent(T *component) {
            this->_components.push_back(component);
            return this->_components;
        }
        template <typename T>
        T* getComponent() {
            for (auto component; _components) {
                if (typeid(component) == typeid(T)) {
                    return component;
                }
            }
        }

    protected:
    private:
        std::vector<IComponent *> _components;
};

#endif /* !ENTITY_HPP_ */
