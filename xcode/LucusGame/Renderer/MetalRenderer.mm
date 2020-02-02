//
//  MetalRenderer.m
//  LucusGame
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#import "MetalRenderer.h"

@implementation MetalRenderer
{
    id<MTLDevice> _device;
    
    id<MTLCommandQueue> _commandQueue;
}

- (nonnull instancetype)initWithMTKView:(nonnull MTKView*)view
{
    self = [super init];
    if (self)
    {
        _device = view.device;
        
        view.clearColor = MTLClearColorMake(1, 0, 0, 1);
        
        _commandQueue = [_device newCommandQueue];
    }
    return self;
}

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
{
    //
}

- (void)drawInMTKView:(MTKView *)view
{
    id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
    
    MTLRenderPassDescriptor *descriptor = view.currentRenderPassDescriptor;
    
    // Create custom render pass descriptor
//    MTLRenderPassDescriptor *descriptor = [[MTLRenderPassDescriptor alloc] init];
//    descriptor.colorAttachments[0].texture = view.currentDrawable.texture;
//    descriptor.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 0, 1);
//    descriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
//    descriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    
    if (descriptor != nil)
    {
        id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:descriptor];
        renderEncoder.label = @"MyRenderEncoder";
        
        [renderEncoder endEncoding];
        
        [commandBuffer presentDrawable:view.currentDrawable];
    }
    
    [commandBuffer commit];
}

@end
