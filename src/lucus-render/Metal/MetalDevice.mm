//
//  MetalDevice.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#include "MetalDevice.h"
#include "MetalRenderSystem.h"

using namespace LucusEngine;

MetalDevice::MetalDevice(MetalRenderSystem* renderSystem) :
    mRenderSystem(renderSystem),
    mDevice(0),
    mCommandQueue(0)
{
    //
}

void MetalDevice::Init()
{
    @autoreleasepool {
        mDevice = MTLCreateSystemDefaultDevice();
        mCommandQueue = [mDevice newCommandQueue];
    }
}

MetalDevice::~MetalDevice()
{
    mDevice = 0;
    mCommandQueue = 0;
}
