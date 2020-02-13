//
//  MetalView.m
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#import "MetalView.h"

#include "host.h"

@implementation MetalView

- (nonnull instancetype)initWithFrame:(CGRect)frameRect device:(nullable id<MTLDevice>)device
{
    self = [super initWithFrame:frameRect device:device];
    if (self)
    {
        //
    }
    return self;
}

- (void)renderInView
{
//    AKUUpdate();
//    AKURender();
    AKUTick();
}

- (void)changeViewWidth:(NSUInteger)width height:(NSUInteger)height
{
//    AKUChangeViewSize(width, height);
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
