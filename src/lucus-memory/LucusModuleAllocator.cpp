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

ModuleAllocator::ModuleAllocator(Size size) : mMarker(0), mTotalSize(size)
{
	mBuffer = std::malloc(mTotalSize);
	mBufferAddress = reinterpret_cast<PtrInt>(mBuffer);
}

ModuleAllocator::~ModuleAllocator()
{
	std::free(mBuffer);
}

void* ModuleAllocator::Alloc(Size size, u8 alignment) 
{
	// Check Alignment
	assert(alignment > 0 && alignment <= 128 && ((alignment & (alignment-1)) == 0));

	// Code from Isetta Engine
	PtrInt rawAddress = mBufferAddress + mMarker;
	PtrInt misAlignment = rawAddress & (alignment - 1);
	PtrDiff adjustment = alignment - misAlignment;
	// for the special case when misAlignment = 0
	// make sure we don't shift the address by its alignment
	adjustment = adjustment & (alignment - 1);
	PtrInt alignedAddress = rawAddress + adjustment;
	Size newMarker = mMarker + size + adjustment;

	assert(newMarker <= mTotalSize);

	mMarker = newMarker;

	return reinterpret_cast<void*>(alignedAddress);
}