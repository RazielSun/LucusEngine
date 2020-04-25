//
//  LucusModuleAllocator.h
//  LucusGame
//
//  Created by Alexander Kardakov on 25/04/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#ifndef _LUCUS_ENGINE_MODULEALLOCATOR_H
#define _LUCUS_ENGINE_MODULEALLOCATOR_H

#include "LucusTypes.h"
#include "LucusMemory.h"

namespace LucusEngine
{
	class ModuleAllocator
	{
	public:
		ModuleAllocator() = delete;
		explicit ModuleAllocator(Size size);
		~ModuleAllocator();

		template<typename T, typename... Args>
		T* New(Args&&...);

		void* Alloc(Size size, u8 alignment);

		Size GetMarker() const { return mMarker; }

	protected:
		Size mTotalSize;
		Size mMarker; // top
		void* mBuffer; // bottom
		PtrInt mBufferAddress;
	};

	template<typename T, typename... Args>
	T* ModuleAllocator::New(Args&&... argsList)
	{
		void* buffer = Alloc(sizeof(T), Memory::ALIGNMENT);
		return new (buffer) T(argsList...);
	}
}

#endif /* _LUCUS_ENGINE_MODULEALLOCATOR_H */