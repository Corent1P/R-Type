/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ECS Components & systems Coordinator
*/

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

#include <iostream>
#include <memory>
#include <vector>
#include "IComponent.hpp"
#include "ASystem.hpp"
#include "Entity.hpp"

class Coordinator {
    public:
        Coordinator();
        ~Coordinator() = default;
        void generateNewEntity();
        void generateNewSystem();
        std::vector<std::shared_ptr<Entity>> getEntities();
        std::vector<std::shared_ptr<ISystem>> getSystems();

    private:
        uint16_t _idEntities;
        std::vector<std::shared_ptr<Entity>> _entities;
        std::vector<std::shared_ptr<ISystem>> _systems;
};

#endif /* !COORDINATOR_HPP_ */
