//
//  LucusObject.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 28/12/2020.
//

#ifndef _LUCUS_ENGINE_OBJECT_H
#define _LUCUS_ENGINE_OBJECT_H

#include "LucusTypes.h"

namespace LucusEngine
{
    class Object
    {
    protected:
        Object() = default;
        Object(const Object& copy) {}
        Object& operator=(const Object& rhs) { return *this; }
        virtual ~Object();

        u32 GetRefCount() { return counter; }

    public:
        void AddRef();
        void ReleaseRef();

    private:
        mutable std::atomic<u32> counter { 0 };

    };
}

#endif /* _LUCUS_ENGINE_OBJECT_H */
