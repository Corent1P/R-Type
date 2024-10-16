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
            std::shared_ptr<Entity> generateNewEntity(uint16_t serverId = -1);
            void generateNewSystem(std::shared_ptr<ISystem> sys);
            const std::vector<std::shared_ptr<Entity>> &getEntities() const;
            const std::vector<std::shared_ptr<ISystem>> &getSystems() const;
            std::shared_ptr<Entity> addEntity(void);
            void deleteEntity(std::shared_ptr<Entity> entityToDestroy);

        private:
            std::size_t getNextEntityId(void);
            std::shared_ptr<std::mutex> _mtx;
            std::vector<std::shared_ptr<Entity>> _entities;
            std::vector<std::shared_ptr<ISystem>> _systems;
    };
}
std::ostream &operator<<(std::ostream &s, const RType::Coordinator &coordinator);
#endif /* !COORDINATOR_HPP_ */
