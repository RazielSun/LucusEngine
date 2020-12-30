
#include "LucusRenderCore.h"
#include "LucusCore.h"
#include "LucusMemoryManager.h"
#include "LucusMetalRenderSystem.h"

#if defined(TARGET_IOS)
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

LucusEngine::RenderSystem* CreateRenderSystem(u32 width, u32 height)
{
    // Create Render System
    LucusEngine::MetalRenderSystem* renderSystem = LucusEngine::Core::GetMemoryManager()->NewOnModule<LucusEngine::MetalRenderSystem>();
    
    // Create Window
    LucusEngine::RenderWindow* window = renderSystem->CreateRenderWindow(width, height);
    LucusEngine::MetalWindow* metalWindow = dynamic_cast<LucusEngine::MetalWindow*>(window);
    
    // Add to RootView
    #if defined(TARGET_IOS)
    // TODO
    #else
    NSView* RootView = [[[[NSApplication sharedApplication] mainWindow] contentViewController] view];
    [RootView addSubview:metalWindow->mView];
    #endif

    return dynamic_cast<LucusEngine::RenderSystem*>(renderSystem);
}