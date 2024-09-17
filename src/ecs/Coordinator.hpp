/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ECS Components & systems Coordinator
*/

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_
#include <iostream>
#include "IComponent.hpp"
#include "ISystem.hpp"
#include "Entity.cpp"
#include "vector"

class Coordinator {
    public:
        Coordinator();
        ~Coordinator();
        generateNewEntity();
        generateNewSystem();
        std::vector<Entity *> getEntities();
        std::vector<ISystem *> getSystems();
        
    protected:
    private:
        std::vector<Entity *> _entities;
        std::vector<ISystem *> _systems;
};

#endif /* !COORDINATOR_HPP_ */
