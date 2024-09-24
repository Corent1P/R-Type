/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** handling event system
*/

#ifndef HANDLEEVENTSYTEM_HPP_
#define HANDLEEVENTSYTEM_HPP_
#include "../ISystem.hh"

#define GET_WINDOW e->getComponent<RType::SFWindowComponent>()->getWindow()
#define GET_WINDOW_SET_ISOPEN e->getComponent<RType::SFWindowComponent>()

class HandleEventSystem: public  RType::ISystem {
    public:
        HandleEventSystem();
        ~HandleEventSystem();
        void effect(std::vector<std::shared_ptr<RType::Entity>> entities);
        bool verifyRequiredComponent(std::shared_ptr<RType::Entity> entity);
        RType::SystemType getType() const;
        //std::string getOutput() const;
    protected:
    private:
        RType::SystemType _type;
        std::vector<std::shared_ptr<RType::Entity>> _entities;
};

#endif /* !HANDLEEVENTSYTEM_HPP_ */
