/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ECS Components & systems Coordinator
*/

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

#include "ASystem.hpp"
#include "Entity.hpp"

class Coordinator {
    public:
        Coordinator();
        ~Coordinator() = default;
        std::shared_ptr<Entity> generateNewEntity();
        void generateNewSystem();
        std::vector<std::shared_ptr<Entity>> getEntities() const;
        std::vector<std::shared_ptr<ISystem>> getSystems() const;

    private:
        uint16_t _idEntities;
        std::vector<std::shared_ptr<Entity>> _entities;
        std::vector<std::shared_ptr<ISystem>> _systems;
};
// std::ostream &operator<<(std::ostream &s, const Coordinator &coordinator);

#endif /* !COORDINATOR_HPP_ */
