//
//  AppDelegate.h
//  LucusGame macOS
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    NSView* _view;
    NSViewController* _viewController;
    NSWindow* _window;
}

@end
