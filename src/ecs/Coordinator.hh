/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** ECS Components & systems Coordinator
*/

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

#include "ASystem.hh"
#include "Entity.hpp"
namespace RType {

    class Coordinator {
        public:
            Coordinator();
            ~Coordinator() = default;
            std::shared_ptr<Entity> generateNewEntity();
            void generateNewSystem(std::shared_ptr<ISystem> sys);
            std::vector<std::shared_ptr<Entity>> getEntities() const;
            std::vector<std::shared_ptr<ISystem>> getSystems() const;
            void deleteEntity(std::shared_ptr<Entity> entityToDestroy);
        private:
            uint16_t _idEntities;
            std::vector<std::shared_ptr<Entity>> _entities;
            std::vector<std::shared_ptr<ISystem>> _systems;
    };
}
std::ostream &operator<<(std::ostream &s, const RType::Coordinator &coordinator);
#endif /* !COORDINATOR_HPP_ */
