//
//  LucusMemoryManager.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 25/04/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusMemoryManager.h"
#include "LucusMemory.h"

using namespace LucusEngine;

MemoryManager::MemoryManager() :
	moduleAllocator(10_MB),
    stackAllocator(10_MB)
{
	//
}

MemoryManager::~MemoryManager() {}
