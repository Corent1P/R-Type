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
#include "../IComponent.hh"

namespace RType {

    class SFWindowComponent: public RType::IComponent {
        public:
            SFWindowComponent(int screenWidth, int screenHeight);
            ~SFWindowComponent();
            std::shared_ptr<sf::RenderWindow> getWindow() const;
            std::string getOutput() const;
            void setisOpen(bool isOpen);
            bool getIsOpen();
        protected:
        private:
            std::shared_ptr<sf::RenderWindow> _window;
            bool _isOpen;

    };
}

#endif /* !SFWINDOWCOMPONENT_HH_ */
