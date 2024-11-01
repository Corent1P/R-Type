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

    /**
     * @brief EventComponent class for handling the events
     *
     */
    class EventComponent: public RType::IComponent {
        public:
            /**
             * @brief Construct a new Event Component object
             *
             */
            EventComponent() = default;

            /**
             * @brief Destroy the Event Component object
             *
             */
            ~EventComponent() = default;

            /**
             * @brief get the event
             *
             * @return sf::Event& the event
             */
            sf::Event &getEvent();

            /**
             * @brief Get the output of the component
             *
             * @return std::string The output of the component
             */
            std::string getOutput() const;
        protected:
        private:
            /**
             * @brief The event
             *
             */
            sf::Event _event;
    };
}
#endif /* !EVENTCOMPONENT_HH_ */
