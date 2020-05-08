//
//  LucusResource.h
//  LucusGame
//
//  Created by Alexander Kardakov on 08/05/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#ifndef _LUCUS_ENGINE_RESOURCE_H
#define _LUCUS_ENGINE_RESOURCE_H

#include "LucusTypes.h"

namespace LucusEngine
{
	class Resource
	{
	protected:
		Resource() : counter(0) {}
		Resource(const Resource& copy) : counter(0) {}
		Resource& operator=(const Resource& rhs) { return *this; }
		virtual ~Resource();

	public:
		void AddRef();
		void ReleaseRef();

	private:
		mutable u32 counter;
		
	};
}

#endif /* _LUCUS_ENGINE_RESOURCE_H */