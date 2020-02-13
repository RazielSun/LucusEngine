//
//  AppDelegate.h
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//


#if defined(TARGET_IOS)
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

@interface AppDelegate

#if defined(TARGET_IOS)
 : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *Window;
@property (strong, nonatomic) UIViewController *RootVC;
@property (strong, nonatomic) UIView *RootView;

#elif defined(TARGET_OSX)
 : NSObject <NSApplicationDelegate>

@property (strong, nonatomic) NSWindow *Window;
@property (strong, nonatomic) NSViewController *RootVC;
@property (strong, nonatomic) NSView *RootView;

#endif

- (nonnull instancetype)init;

+ (nullable AppDelegate*)sharedDelegate;

@end
