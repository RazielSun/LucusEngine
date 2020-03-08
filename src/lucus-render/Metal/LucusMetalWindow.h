//
//  MetalWindow.h
//  LucusGame
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#ifndef _LUCUS_ENGINE_METAL_WINDOW_H
#define _LUCUS_ENGINE_METAL_WINDOW_H

#include "LucusRenderWindow.h"
#include "LucusMetalView.h"
#include "LucusMetalDevice.h"

#if defined(TARGET_IOS)
#import <UIKit/UIKit.h>
#elif defined(TARGET_OSX)
#import <Cocoa/Cocoa.h>
#endif

namespace LucusEngine
{
    class MetalWindow: public RenderWindow
    {
    public:
        MetalWindow(u32 width, u32 height, MetalDevice* device);
        virtual ~MetalWindow();
        
//        virtual void ChangeViewportSize(u32 width, u32 height) override;
        
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
