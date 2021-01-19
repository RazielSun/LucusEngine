
#include "wrap_Core.h"
#include "LucusLuaState.h"
#include "LucusLuaStack.h"

#include "LucusCore.h"
#include "LucusWorld.h"

using namespace LucusEngine;

#define LUCUS_LUA_CORE_CLASS "core"
#define WORLD_PROPERTY "world"

#define IS_PROPERTY(value, property) (strcmp(value, property) == 0)

static int core_index(lua_State* L)
{
    if (lua_gettop(L) != 2) return -1;
    LuaStack stack(L);
    Core* core = stack.GetLuaObject<Core>(1);
    auto property = stack.GetValue<cc8*>(2, "none");
    if (IS_PROPERTY(property, WORLD_PROPERTY))
    {
        // TODO: Push Ref
        // core->GetWorld()
        std::cout << "[C++] core_index[ " << property << " ]\n";
    }
    return 0;
}

static int core_newindex(lua_State* L)
{
    if (lua_gettop(L) != 3) return -1;
    LuaStack stack(L);
    Core* core = stack.GetLuaObject<Core>(1);
    auto property = stack.GetValue<cc8*>(2, "none");
    World* world = stack.GetLuaObject<World>(3);
    if (IS_PROPERTY(property, WORLD_PROPERTY))
    {
        std::cout << "[C++] core_newindex[ " << property << " ] = " << world << std::endl;
        core->SetWorld(world);
    }
    return 0;
}

static int core_gc(lua_State* L)
{
    return 0;
}

static const luaL_Reg core_meta[] = {
    { "__index", core_index },
    { "__newindex", core_newindex },
    { "__gc", core_gc },
    { 0, 0 }
};

namespace LucusEngine
{
    void InitializeCore(LuaState* state)
    {
        lua_State* L = state->GetRawLua();

        lua_getglobal(L, LUCUS_LUA_MAIN_MODULE);

        Core** pptr = static_cast<Core**>(lua_newuserdata(L, sizeof(Core*)));
        *pptr = Core::GetPtr();
        int core_idx = lua_gettop(L);

        lua_newtable(L);
        luaL_setfuncs(L, core_meta, 0);
        lua_setmetatable(L, core_idx);

        lua_setfield(L, -2, LUCUS_LUA_CORE_CLASS);
        
        lua_pop(L, 1);
    }
}
