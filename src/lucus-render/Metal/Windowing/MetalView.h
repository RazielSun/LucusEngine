//
//  MetalView.h
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 12/02/2020.
//

#ifndef _METAL_VIEW_H
#define _METAL_VIEW_H

#import <MetalKit/MTKView.h>

@interface MetalView : MTKView

- (nonnull instancetype)initMetalViewWithWidth:(NSUInteger)width height:(NSUInteger)height;

- (void)renderInView;
- (void)changeViewWidth:(NSUInteger)width height:(NSUInteger)height;

@end

#endif /* _METAL_VIEW_H */
