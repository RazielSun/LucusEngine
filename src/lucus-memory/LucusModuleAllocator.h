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
		explicit ModuleAllocator(size_t size);
		~ModuleAllocator();

		template<typename T, typename... Args>
		T* New(Args&&...);

		void* Alloc(size_t size, u8 alignment);

		size_t GetMarker() const { return mMarker; }

	protected:
		size_t mTotalSize;
		size_t mMarker; // top
		void* mBuffer; // bottom
		uintptr mBufferAddress;
	};

	template<typename T, typename... Args>
	T* ModuleAllocator::New(Args&&... argsList)
	{
		void* buffer = Alloc(sizeof(T), Memory::ALIGNMENT);
		return new (buffer) T(argsList...);
	}
}

#endif /* _LUCUS_ENGINE_MODULEALLOCATOR_H */
