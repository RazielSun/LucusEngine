//
//  MetalRenderer.h
//  LucusGame
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#import <MetalKit/MetalKit.h>

@interface MetalRenderer : NSObject<MTKViewDelegate>

- (nonnull instancetype)initWithMTKView:(nonnull MTKView*)view;

@end

