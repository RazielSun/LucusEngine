//
//  LucusSceneComponent.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 2/04/2020.
//

#include "LucusSceneComponent.h"
#include "LucusSceneComponentProxy.h"
#include "LucusLuaStack.h"

using namespace LucusEngine;

SceneComponent::SceneComponent() :
    mTransform(),
    Proxy(nullptr),
    mParent(nullptr)
{
    //
}

SceneComponent::~SceneComponent()
{
    //
}

void SceneComponent::Tick(float deltaSeconds)
{
    ChildIt it = mChildren.begin();
    for (;it != mChildren.end(); ++it)
    {
        (*it)->Tick(deltaSeconds);
    }
}

void SceneComponent::LateTick()
{
    UpdateCachedModelMatrix();

    ChildIt it = mChildren.begin();
    for (;it != mChildren.end(); ++it)
    {
        (*it)->LateTick();
    }
}

void SceneComponent::AttachTo(SceneComponent* parent)
{
    if (parent != nullptr)
    {
        parent->AddChild(this);
        mParent = parent;
    }
}

void SceneComponent::Detach()
{
    if (mParent)
    {
        mParent->RemoveChild(this);
        mParent.Reset();
    }
}

void SceneComponent::AddChild(SceneComponent* child)
{
    if (child != nullptr)
    {
        Ptr<SceneComponent> childPtr(child);
        mChildren.push_back(childPtr);
    }
}

void SceneComponent::RemoveChild(SceneComponent* child)
{
    // remove child
}

void SceneComponent::UpdateCachedModelMatrix()
{
    mTransform.UpdateMatrices();
    if (mParent.IsNull())
    {
        mTransform.SetCachedWorldMatrix(mTransform.GetModelMatrix());
    }
    else
    {
        mTransform.SetCachedWorldMatrix(mTransform.GetModelMatrix() * mParent->GetModelMatrix());
    }
}

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
