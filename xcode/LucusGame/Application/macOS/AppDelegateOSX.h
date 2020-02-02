//
//  AppDelegate.h
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>
#import "MetalRenderer.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    MTKView* _view;
    NSViewController* _viewController;
    NSWindow* _window;
    MetalRenderer *_renderer;
}

@end

