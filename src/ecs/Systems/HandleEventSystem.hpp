/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** handling event system
*/

#ifndef HANDLEEVENTSYTEM_HPP_
#define HANDLEEVENTSYTEM_HPP_
#include "../ASystem.hh"

#define GET_WINDOW entity->getComponent<RType::SFWindowComponent>()->getWindow()
#define GET_WINDOW_SET_ISOPEN entity->getComponent<RType::SFWindowComponent>()

class HandleEventSystem: public  RType::ASystem {
    public:
        HandleEventSystem();
        ~HandleEventSystem();
        void effect(std::shared_ptr<RType::Entity> entity);
        bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        RType::SystemType getType() const;
    protected:
    private:
        RType::SystemType _type;
};

#endif /* !HANDLEEVENTSYTEM_HPP_ */
