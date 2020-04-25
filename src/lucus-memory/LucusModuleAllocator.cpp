//
//  LucusModuleAllocator.h
//  LucusGame
//
//  Created by Alexander Kardakov on 25/04/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusModuleAllocator.h"
#include <assert.h>

using namespace LucusEngine;

ModuleAllocator::ModuleAllocator(size_t size) : mMarker(0), mTotalSize(size)
{
	mBuffer = std::malloc(mTotalSize);
	mBufferAddress = reinterpret_cast<uintptr>(mBuffer);
}

ModuleAllocator::~ModuleAllocator()
{
	std::free(mBuffer);
}

void* ModuleAllocator::Alloc(size_t size, u8 alignment)
{
	// Check Alignment
	assert(alignment > 0 && alignment <= 128 && ((alignment & (alignment-1)) == 0));

	// Code from Isetta Engine
	uintptr rawAddress = mBufferAddress + mMarker;
	uintptr misAlignment = rawAddress & (alignment - 1);
	sintptr adjustment = alignment - misAlignment;
	// for the special case when misAlignment = 0
	// make sure we don't shift the address by its alignment
	adjustment = adjustment & (alignment - 1);
	uintptr alignedAddress = rawAddress + adjustment;
	size_t newMarker = mMarker + size + adjustment;

	assert(newMarker <= mTotalSize);

	mMarker = newMarker;

	return reinterpret_cast<void*>(alignedAddress);
}
