//
//  AppDelegate.m
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#import "AppDelegateOSX.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    NSRect bounds = NSMakeRect(0, 0, 1280, 720);
    _view = [[NSView alloc] initWithFrame:bounds];
    
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