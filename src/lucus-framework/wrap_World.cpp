
#include "wrap_World.h"
#include "LucusLuaState.h"
#include "LucusLuaFactory.h"

#include "LucusWorld.h"

using namespace LucusEngine;

void World::BindLuaFunctions(lua_State* lua)
{
    const luaL_Reg reg_table[] = {
        { "AddActor", _addActor },
        { 0, 0 }
    };
    luaL_setfuncs(lua, reg_table, 0);
    lua_pushvalue(lua, -1);
}

int World::_addActor(lua_State* lua)
{
    LuaStack stack(lua);
    World* world = stack.GetLuaObject<World>(1);
    Actor* actor = stack.GetLuaObject<Actor>(2);
    if (world != nullptr && actor != nullptr)
    {
        std::cout << "[C++] World _addActor called.\n";
        std::cout << "[C++] World " << world << ", Actor " << actor << ".\n";
        world->AddActor(actor);
    }
    return 0;
}

static const luaL_Reg World_methods = {
    { "AddActor", _addActor },
    { 0, 0 }
}

static int World_gc(lua_State* L)
{
    return 0;
}

static const luaL_Reg World_meta = {
    { "__gc", World_gc },
    { 0, 0 }
}

void InitializeWorld(LuaState* state)
{
    //
}
