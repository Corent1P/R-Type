/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Menu component
*/

#pragma once

#include "../IComponent.hh"

#define GET_MENU getComponent<RType::MenuComponent>()

namespace RType {
    enum Menu {
        EVERYWHERE,
        HOME,
        MAPPING_INPUT,
        LOADING,
        GAME
    };
    class MenuComponent: public RType::IComponent {
        public:
            MenuComponent(Menu menu);
            ~MenuComponent();
            void setMenu(Menu menu);
            RType::Menu getMenu() const;
            std::string getOutput() const;
            bool operator==(const MenuComponent &other) const;
        private:
            Menu _menu;
    };
}
