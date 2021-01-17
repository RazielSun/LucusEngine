
#include "wrap_Actor.h"
#include "LucusLuaState.h"
#include "LucusLuaFactory.h"

#include "LucusActor.h"

using namespace LucusEngine;

void SceneComponent::BindLuaFunctions(lua_State* lua)
{
    LuaObject::BindLuaFunctions(lua);
    
    const luaL_Reg reg_table[] = {
        { "AddChild", _addChild },
        { "RemoveChild", _removeChild },
        { "AttachTo", _attachTo },
        { "Detach", _detach },
        { "SetLocation", _setLocation },
        { 0, 0 }
    };
    luaL_setfuncs(lua, reg_table, 0);
    lua_pushvalue(lua, -1);
}

int SceneComponent::_addChild(lua_State* L)
{
    LuaStack stack(L);
    SceneComponent* parent = stack.GetLuaObject<SceneComponent>(1);
    SceneComponent* child = stack.GetLuaObject<SceneComponent>(2);
    if (parent != nullptr && child != nullptr)
    {
        child->AttachTo(parent);
    }
    return 0;
}

int SceneComponent::_removeChild(lua_State* L)
{
    return 0;
}

int SceneComponent::_attachTo(lua_State* L)
{
    return 0;
}

int SceneComponent::_detach(lua_State* L)
{
    return 0;
}

int SceneComponent::_setLocation(lua_State* L)
{
    LuaStack stack(L);
    SceneComponent* comp = stack.GetLuaObject<SceneComponent>(1);
    float x = stack.GetValue<float>(2, 0.f);
    float y = stack.GetValue<float>(3, 0.f);
    float z = stack.GetValue<float>(4, 0.f);
    if (comp != nullptr)
    {
        comp->mTransform.SetLocation(x, y, z);
    }
    return 0;
}


void MeshComponent::BindLuaFunctions(lua_State* lua)
{
    SceneComponent::BindLuaFunctions(lua);
    
    const luaL_Reg reg_table[] = {
        { "SetMesh", _setMesh },
        { "SetImage", _setImage },
        { 0, 0 }
    };
    luaL_setfuncs(lua, reg_table, 0);
    lua_pushvalue(lua, -1);
}
    
int MeshComponent::_setMesh(lua_State* L)
{
    LuaStack stack(L);
    MeshComponent* comp = stack.GetLuaObject<MeshComponent>(1);
    cc8* meshName = stack.GetValue<cc8*>(2, "");
    if (comp != nullptr)
    {
        comp->SetMesh(meshName);
    }
    return 0;
}

int MeshComponent::_setImage(lua_State* L)
{
    LuaStack stack(L);
    MeshComponent* comp = stack.GetLuaObject<MeshComponent>(1);
    cc8* imageName = stack.GetValue<cc8*>(2, "");
    if (comp != nullptr)
    {
        comp->SetImage(imageName);
    }
    return 0;
}

void InitializeComponents(LuaState* state)
{
    //
}