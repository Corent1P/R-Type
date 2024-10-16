/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** action component asign to a entity
*/

#ifndef ACTIONCOMPONENT_HPP_
#define ACTIONCOMPONENT_HPP_
#include "../IComponent.hh"

namespace RType {
    enum Action {
        NOTHING,
        SHOOTING,
    };

    class ActionComponent: public RType::IComponent {
        public:
            ActionComponent(Action Action);
            ActionComponent();
            ~ActionComponent();
            void setAction(Action entityType);
            Action getAction() const;
            void setActions(Action direction, bool newBool);
            bool getActions(Action direction) const;
            std::string getOutput() const;
        private:
            Action _action;
            std::vector<bool> _actions;
    };
}
#endif /* !ACTIONCOMPONENT_HPP_ */
