/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** SFML window component
*/

#ifndef SFWINDOWCOMPONENT_HH_
#define SFWINDOWCOMPONENT_HH_
#include <SFML/Graphics.hpp>
#include "../Include.hh"

class SFWindowComponent {
    public:
        SFWindowComponent(int screenWidth, int screenHeight);
        ~SFWindowComponent();
        void setRenderWindow(int screenWidth, int screenHeight);
        sf::RenderWindow getWindow() const;
    protected:
    private:
        std::shared_ptr<sf::RenderWindow> _window;

};

#endif /* !SFWINDOWCOMPONENT_HH_ */
