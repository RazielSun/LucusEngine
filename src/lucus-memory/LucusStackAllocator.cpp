//
//  LucusStackAllocator.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 25/04/2020.
//  Copyright © 2020 Alexander Kardakov. All rights reserved.
//

#include "LucusStackAllocator.h"
#include <assert.h>

using namespace LucusEngine;

StackAllocator::StackAllocator(Size size) : mMarker(0), mTotalSize(size)
{
	mBuffer = std::malloc(mTotalSize);
	mBufferAddress = reinterpret_cast<PtrInt>(mBuffer);
}

StackAllocator::~StackAllocator()
{
	std::free(mBuffer);
}

void* StackAllocator::Alloc(Size size, u8 alignment) 
{
	// Check Alignment
	assert(alignment > 0 && alignment <= 128 && ((alignment & (alignment-1)) == 0));

	// this is non-standard
	// if(!numBytes)
	// 	return 0;

	// uintptr_t unalignedStart = uintptr_t(mFreeStart) + sizeof(Header);

	// byte* allocStart = reinterpret_cast<byte*>((unalignedStart + (align - 1)) & ~(align - 1));
	// byte* allocEnd = allocStart + numBytes;

	// // ensure there is space for the alloc
	// PX_ASSERT(allocEnd <= mBuffer + mBufferSize);

	// Header* h = getHeader(allocStart);
	// h->mPrev = mTop;
	// h->mSize = numBytes;
	// h->mFree = false;

	// mTop = h;
	// mFreeStart = allocEnd;

	// return allocStart;
	return nullptr;
}