/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Event Component
*/

#ifndef EVENTCOMPONENT_HH_
#define EVENTCOMPONENT_HH_
#include <SFML/Graphics.hpp>
#include "../IComponent.hh"

namespace RType {

    class EventComponent: public RType::IComponent {
        public:
            EventComponent() = default;
            ~EventComponent() = default;
            const sf::Event &getEvent() const;
            std::string getOutput() const;
        protected:
        private:
            sf::Event _event;
    };
}
#endif /* !EVENTCOMPONENT_HH_ */
