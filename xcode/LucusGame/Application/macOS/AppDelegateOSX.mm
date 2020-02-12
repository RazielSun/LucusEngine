//
//  AppDelegate.m
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#import "AppDelegateOSX.h"
#import <MetalKit/MetalKit.h>
//#import "MetalRenderer.h"
//#import "MetalView.h"

#include "host.h"
#include "MetalView.h"

//#include "LucusCore.h"
//#include "MetalRenderSystem.h"

@interface AppDelegate()
{
    NSViewController* _viewController;
    NSWindow* _window;
    MetalView* _view;
//    MetalRenderer *_renderer;
}

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    // Init Engine
    AKUCoreCreate();
    
    NSUInteger width = 1280;
    NSUInteger height = 720;
    
    _view = [[MetalView alloc] initMetalViewWithWidth:width height:height];
    
//    _renderer = [[MetalRenderer alloc] initWithMTKView:_view];
//    _view.delegate = _renderer;
    
    _viewController = [[NSViewController alloc] init];
    _viewController.view = _view;
    
    _window = [NSWindow windowWithContentViewController:_viewController];
    _window.title = @"Lucus Game";
    [_window makeKeyAndOrderFront:self];
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}


- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}


@end
