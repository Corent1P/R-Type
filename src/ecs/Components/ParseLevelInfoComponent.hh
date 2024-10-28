/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParseLevelInfoComponent
*/

#include <lua.hpp>
#include <lualib.h>
#include <lua.h>
#include <lauxlib.h>

#include "../IComponent.hh"

#pragma once

namespace RType {
    /**
     * @brief  ParseLevelInfoComponent class
     */
    class ParseLevelInfoComponent : public RType::IComponent {
    public:
        /**
         * @brief Construct a new ParseLevelInfoComponent object
         * 
         * @param level 
         */
        ParseLevelInfoComponent(int level);

        /**
         * @brief Destroy the ParseLevelInfoComponent object
         * 
         */
        ~ParseLevelInfoComponent();

        /**
         * @brief Set the Level object
         * 
         * @param level 
         */
        void setLevel(int level);

        /**
         * @brief Get the Level object
         * 
         * @return int 
         */
        int getLevel() const;

        /**
         * @brief Set the Function Pushed object
         * 
         * @param functionPushed 
         */
        void setFunctionPushed(bool functionPushed);

        /**
         * @brief Get the Function Pushed object
         * 
         * @return bool 
         */
        bool getFunctionPushed() const;

        /**
         * @brief Set the Lua State object
         * 
         * @param L 
         */
        lua_State *getLuaState() const;

        /**
         * @brief Get the Lua State object
         * 
         * @return lua_State* 
         */
        std::string getOutput() const;
    private:
        /**
         * @brief Level the current level of the game
         */
        int _level;

        /**
         * @brief FunctionPushed check if the createEntity function has been pushed
         * to the lua file
         */
        bool _functionPushed;

        /**
         * @brief Lua State the lua state
         */
        lua_State *_luaState;
    };
}
