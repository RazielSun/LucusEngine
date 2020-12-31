//
//  LucusLuaObject.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 29/12/2020.
//

#ifndef _LUCUS_ENGINE_LUA_OBJECT_H
#define _LUCUS_ENGINE_LUA_OBJECT_H

#include "LucusObject.h"
#include "LucusLuaState.h"

#define DECL_LUA_OBJECT(type)                       \
cc8* GetTypeName() const { return #type; }

namespace LucusEngine
{
    class LuaObject : public Object
    {
    public:
        virtual void BindLuaFunctions(lua_State* lua);
    };
}

#endif /* _LUCUS_ENGINE_LUA_OBJECT_H */
