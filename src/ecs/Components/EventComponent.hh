/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Event Component
*/

#ifndef EVENTCOMPONENT_HH_
#define EVENTCOMPONENT_HH_
#include <SFML/Graphics.hpp>

class EventComponent {
    public:
        EventComponent();
        ~EventComponent();
        void setEvent();
        sf::Event getEvent() const;
    protected:
    private:
        sf::Event _event;
};

#endif /* !EVENTCOMPONENT_HH_ */
