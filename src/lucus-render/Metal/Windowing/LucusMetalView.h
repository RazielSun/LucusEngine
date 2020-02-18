//
//  LucusMetalView.h
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#ifndef _LUCUS_ENGINE_METAL_VIEW_H
#define _LUCUS_ENGINE_METAL_VIEW_H

#import <MetalKit/MTKView.h>

@interface MetalView : MTKView

- (nonnull instancetype)initWithFrame:(CGRect)frameRect device:(nullable id<MTLDevice>)device;

- (void)renderInView;
- (void)changeViewWidth:(NSUInteger)width height:(NSUInteger)height;

@end

#endif /* _LUCUS_ENGINE_METAL_VIEW_H */
