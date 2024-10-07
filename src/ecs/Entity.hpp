/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Entity file
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "IComponent.hh"

namespace RType {

    class Entity {
        public:
            Entity(uint16_t id, std::shared_ptr<std::mutex> mtx, uint16_t serverId = -1);
            ~Entity() = default;

            std::vector<std::shared_ptr<IComponent>> getComponents(void) const;
            uint16_t getId(void) const;
            uint16_t getServerId(void) const;
            void setServerId(uint16_t serverId);

            template <typename T>
            std::shared_ptr<T> pushComponent(std::shared_ptr<T> component) {
                std::unique_lock<std::mutex> lock(*_mtx);
                this->_components.push_back(component);
                return component;
            }

            template <typename T>
            std::shared_ptr<T> getComponent() const {
                std::unique_lock<std::mutex> lock(*_mtx);
                for (const auto& component : _components) {
                    std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
                    if (castedComponent) {
                        return castedComponent;
                    }
                }
                return nullptr;
            }

            void clearComponents(void);

        private:
            std::vector<std::shared_ptr<IComponent>> _components;
            uint16_t _id;
            std::shared_ptr<std::mutex> _mtx;
            uint16_t _serverId;

    };
}
std::ostream &operator<<(std::ostream &s, const RType::Entity &entity);

#endif /* !ENTITY_HPP_ */
