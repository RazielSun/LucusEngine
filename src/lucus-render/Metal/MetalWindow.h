//
//  MetalWindow.hpp
//  LucusGame
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#ifndef _METAL_WINDOW_H
#define _METAL_WINDOW_H

#include "LucusWindow.h"
#include "MetalView.h"
#include "MetalDevice.h"

#if defined(TARGET_IOS)
#import <UIKit/UIKit.h>
#elif defined(TARGET_OSX)
#import <Cocoa/Cocoa.h>
#endif

namespace LucusEngine
{
    class MetalWindow: public Window
    {
    public:
        MetalWindow(u32 width, u32 height, MetalDevice* device);
        virtual ~MetalWindow();
        
    public:
        MetalView* mView;
        
        CAMetalLayer* mMetalLayer;
        id<CAMetalDrawable> mCurrentDrawable;
        
#if defined(TARGET_IOS)
        UIWindow *mWindow;
        UIViewController *mViewController;
#elif defined(TARGET_OSX)
        NSViewController* mViewController;
        NSWindow* mWindow;
#endif
    };
}

#endif /* _METAL_WINDOW_H */
