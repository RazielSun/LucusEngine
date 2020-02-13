//
//  MetalWindow.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#include "MetalWindow.h"

using namespace LucusEngine;

MetalWindow::MetalWindow(u32 width, u32 height, MetalDevice* device) : Window(width, height)
{
    @autoreleasepool {
        CGRect frame = CGRectMake(0, 0, mWidth, mHeight);
        mView = [[MetalView alloc] initWithFrame:frame device:device->mDevice];
        
        mMetalLayer = (CAMetalLayer*)mView.layer;
        
//    #if defined(TARGET_IOS)
//        mViewController = [[UIViewController alloc] init];
//        mViewController.view = mView;
//
//        mWindow = [[UIWindow alloc] init];
//        mWindow.rootViewController = mViewController;
//        [mWindow makeKeyAndVisible];
//    #elif defined(TARGET_OSX)
//        mViewController = [[NSViewController alloc] init];
//        mViewController.view = mView;
//
//        mWindow = [NSWindow windowWithContentViewController:mViewController];
//        mWindow.title = @"Lucus Game";
////        [mWindow makeKeyAndOrderFront:self];
//    #endif
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
