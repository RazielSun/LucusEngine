//
//  LucusMemoryManager.h
//  LucusGame
//
//  Created by Alexander Kardakov on 25/04/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#ifndef _LUCUS_ENGINE_MEMORYMANAGER_H
#define _LUCUS_ENGINE_MEMORYMANAGER_H

#include "LucusModuleAllocator.h"
#include "LucusStackAllocator.h"

namespace LucusEngine
{
	class MemoryManager
	{
	public:
		MemoryManager();
		~MemoryManager();

		template<typename T, typename... Args>
		T* NewOnStack(Args&&...);

		template<typename T, typename... Args>
		T* NewOnModule(Args&&...);

	protected:
		ModuleAllocator moduleAllocator;
		StackAllocator stackAllocator;
		
	};

	template<typename T, typename... Args>
	T* MemoryManager::NewOnStack(Args&&... argsList)
	{
		return stackAllocator.New<T>(std::forward(argsList)...);
	}

	template<typename T, typename... Args>
	T* MemoryManager::NewOnModule(Args&&... argsList)
	{
		return moduleAllocator.New<T>(std::forward(argsList)...);
	}
}

#endif /* _LUCUS_ENGINE_MEMORYMANAGER_H */