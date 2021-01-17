
#include "wrap_Actor.h"
#include "LucusLuaState.h"
#include "LucusLuaFactory.h"

#include "LucusActor.h"

using namespace LucusEngine;

#define LUA_LIB_NAME "lucus"
#define LUA_TYPE_NAME_ACTOR "actor"

// void Actor::BindLuaFunctions(lua_State* lua)
// {
//     LuaObject::BindLuaFunctions(lua);
    
    
//     luaL_setfuncs(lua, reg_table, 0);
//     lua_pushvalue(lua, -1);
// }

static int _setRootComponent(lua_State* L)
{
    LuaStack stack(L);
    Actor* actor = stack.GetLuaObject<Actor>(1);
    SceneComponent* comp = stack.GetLuaObject<SceneComponent>(2);
    if (actor != nullptr && comp != nullptr)
    {
        std::cout << "[C++] Actor SetRootComponent called.\n";
        actor->SetRootComponent(comp);
    }
    return 0;
}

static luaL_Reg Actor_methods[] = {
    { "SetRootComponent", _setRootComponent },
    { 0, 0 }
};

static luaL_Reg Actor_meta[] = {
    { "__gc", LuaFactory<Actor>::_gc },
    { 0, 0 }
};

void InitializeActor(LuaState* state)
{
    // const u32 total_count = 1;
    // struct
    // {
    //     cc8* Name;
    //     const luaL_Reg* Methods;
    //     const luaL_Reg* Meta;
    // } types[total_count] = {
    //     { , Actor_methods, Actor_meta }
    // };
    // for (u32 i = 0; i < total_count; i++)
    // {
    //     ::Re
    // }
    LuaFactory<Actor>::RegisterUserClass(state, LUA_TYPE_NAME_ACTOR, LUA_LIB_NAME);
    // RegisterUserMetatable(state, LUA_TYPE_NAME_ACTOR, Actor_methods, Actor_meta);
}