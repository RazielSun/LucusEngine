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
        Object() : counter(0) {}
		Object(const Object& copy) : counter(0) {}
		Object& operator=(const Object& rhs) { return *this; }
		virtual ~Object();

    public:
		void AddRef();
		void ReleaseRef();

	private:
		mutable u32 counter;

    };
}

#endif /* _LUCUS_ENGINE_OBJECT_H */
