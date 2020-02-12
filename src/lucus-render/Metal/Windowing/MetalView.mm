//
//  MetalView.m
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#import "MetalView.h"

#include "host.h"
#include "MetalRenderSystem.h"

@implementation MetalView

- (nonnull instancetype)initMetalViewWithWidth:(NSUInteger)width height:(NSUInteger)height
{
//    #if defined(TARGET_IOS)
    CGRect frame = CGRectMake(0.0, 0.0, width, height);
//    #elif defined(TARGET_OSX)
//    NSRect frame = NSMakeRect(0.0, 0.0, width, height);
//    #endif
    
    LucusEngine::MetalRenderSystem* renderSystem = new LucusEngine::MetalRenderSystem();
    renderSystem->Init();
    
    self = [super initWithFrame:frame device:renderSystem->mDevice];
    if (self)
    {
        self.clearColor = MTLClearColorMake(1, 0, 0, 1);
        
        renderSystem->RegisterView(self);
        
        AKUSetRenderSystem(static_cast<LucusEngine::RenderSystem*>(renderSystem));
    }
    return self;
}

- (void)renderInView
{
    AKUUpdate();
    AKURender();
}

- (void)changeViewWidth:(NSUInteger)width height:(NSUInteger)height
{
    AKUChangeViewSize(width, height);
}

#if defined(TARGET_IOS)

- (void)drawRect:(CGRect)rect
{
    [super drawRect:rect];
    
    [self renderInView];
}

- (void)setFrame:(CGRect)frame
{
    [super setFrame:frame];
    
    [self changeViewWidth:frame.size.width height:frame.size.height];
}

#elif defined(TARGET_OSX)

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    
    [self renderInView];
}

- (void) setFrameSize:(NSSize)newSize
{
    [super setFrameSize:newSize];
    
    [self changeViewWidth:newSize.width height:newSize.height];
}

#endif

@end
