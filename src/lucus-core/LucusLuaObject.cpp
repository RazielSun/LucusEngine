//
//  LucusLuaObject.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 28/12/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusLuaObject.h"

using namespace LucusEngine;

LuaObject::LuaObject()
{
    //
}

LuaObject::~LuaObject()
{
    //
}

void LuaObject::BindLuaFunctions(lua_State* lua)
{
    const luaL_Reg reg_table[] = {
        { "GetClassName", _getClassName },
        { 0, 0 }
    };
    luaL_setfuncs(lua, reg_table, 0);
    lua_pushvalue(lua, -1);
}


int LuaObject::_getClassName(lua_State* L)
{
    return 0;
}
