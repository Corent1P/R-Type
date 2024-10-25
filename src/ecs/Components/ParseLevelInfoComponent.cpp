/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParseLevelInfoComponent
*/

#include "ParseLevelInfoComponent.hh"

RType::ParseLevelInfoComponent::ParseLevelInfoComponent(int level):
    _level(level), _functionPushed(false), _luaState(nullptr)
{
    std::string lvlName = "./config/level/lvl" + std::to_string(_level) + ".lua";

    _luaState = luaL_newstate();
    luaL_openlibs(_luaState);
    if (luaL_dofile(_luaState, lvlName.c_str()) != 0) {
        std::cerr << "Error: " << lua_tostring(_luaState, -1) << std::endl;
        lua_close(_luaState);
        exit(84);
    }
}

RType::ParseLevelInfoComponent::~ParseLevelInfoComponent()
{
    lua_close(_luaState);
}

void RType::ParseLevelInfoComponent::setLevel(int level)
{
    _level = level;
}

int RType::ParseLevelInfoComponent::getLevel() const
{
    return _level;
}

void RType::ParseLevelInfoComponent::setFunctionPushed(bool functionPushed)
{
    _functionPushed = functionPushed;
}

bool RType::ParseLevelInfoComponent::getFunctionPushed() const
{
    return _functionPushed;
}

lua_State *RType::ParseLevelInfoComponent::getLuaState() const
{
    return _luaState;
}

std::string RType::ParseLevelInfoComponent::getOutput() const
{
    return "ParseLevelInfoComponent";
}
