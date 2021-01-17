//
//  LucusLuaReference.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 16/01/2021.
//

#ifndef _LUCUS_ENGINE_LUA_REFERENCE_H
#define _LUCUS_ENGINE_LUA_REFERENCE_H

class lua_State;

namespace LucusEngine
{
    class LuaReference
    {
    public:
        LuaReference();
        LuaReference(lua_State* L);
        ~LuaReference() noexcept;
        
        void Ref(lua_State* L);
        void Unref();
        void Push() const;

        bool IsValid() const;
    private:
        int mRef;
        lua_State* mLua;
    };
}

#endif /* _LUCUS_ENGINE_LUA_REFERENCE_H */
