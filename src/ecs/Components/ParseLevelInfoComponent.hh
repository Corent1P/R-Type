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
         * @param level Initial level
         */
        ParseLevelInfoComponent(int level);

        /**
         * @brief Destroy the ParseLevelInfoComponent object
         */
        ~ParseLevelInfoComponent();

        /**
         * @brief Set the Level
         *
         * @param level New level
         */
        void setLevel(int level);

        /**
         * @brief Get the Level
         *
         * @return int Current level
         */
        int getLevel() const;

        /**
         * @brief Set the Function Pushed
         *
         * @param functionPushed New function pushed state
         */
        void setFunctionPushed(bool functionPushed);

        /**
         * @brief Get the Function Pushed
         *
         * @return bool Current function pushed state
         */
        bool getFunctionPushed() const;

        /**
         * @brief Get the Lua State
         *
         * @return lua_State* Current Lua state
         */
        lua_State *getLuaState() const;

        /**
         * @brief Get the Output as a string
         *
         * @return std::string Output string
         */
        std::string getOutput() const;

    private:
        /**
         * @brief Current level of the game
         */
        int _level;

        /**
         * @brief Check if the createEntity function has been pushed to the lua file
         */
        bool _functionPushed;

        /**
         * @brief Lua state
         */
        lua_State *_luaState;
    };
}
