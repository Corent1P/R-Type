/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Clock component
*/

#ifndef CLOCKCOMPONENT_HH_
#define CLOCKCOMPONENT_HH_

#include <SFML/Graphics.hpp>
#include "../IComponent.hh"

namespace RType {

    class ClockComponent: public RType::IComponent {
        public:
            ClockComponent() = default;
            ~ClockComponent() = default;
            sf::Clock &getClock();
            std::string getOutput() const;
        private:
            sf::Clock _clock;
    };
}

#endif /* !CLOCKCOMPONENT_HH_ */
