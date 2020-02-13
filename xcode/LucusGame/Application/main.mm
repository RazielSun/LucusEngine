//
//  main.m
//  LucusGame
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#if defined(TARGET_IOS)
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

#import "AppDelegate.h"

#if defined(TARGET_IOS)

int main(int argc, char * argv[]) {
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}

#elif defined(TARGET_OSX)

int main(int argc, const char * argv[]) {
    NSApplication* application = [NSApplication sharedApplication];
    AppDelegate* delegate = [[AppDelegate alloc] init];
    application.delegate = delegate;
    return NSApplicationMain(argc, argv);
}

#endif
