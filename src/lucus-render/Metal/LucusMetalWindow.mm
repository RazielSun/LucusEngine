//
//  MetalWindow.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#include "LucusMetalWindow.h"

using namespace LucusEngine;

MetalWindow::MetalWindow(u32 width, u32 height, MetalDevice* device) : RenderWindow(width, height)
{
    @autoreleasepool {
        CGRect frame = CGRectMake(0, 0, width, height);
        mView = [[MetalView alloc] initWithFrame:frame device:device->mDevice];
        
        mMetalLayer = (CAMetalLayer*)mView.layer;
    }
}

MetalWindow::~MetalWindow()
{
    mView = 0;
    mViewController = 0;
    mWindow = 0;
    mCurrentDrawable = 0;
    mMetalLayer = 0;
}

//void MetalWindow::ChangeViewportSize(u32 width, u32 height)
//{
    // Change here viewport size for Window and View
    
    // CAMetalLayer drawableSize = width/ height
    
    // MetalView change buffers automatically with autoresizing mask properties
//}
