//
//  AppDelegate.m
//  LucusGame iOS
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#import "AppDelegateIOS.h"

#include "host.h"
#include "MetalView.h"

//#import <MetalKit/MetalKit.h>
//#import "MetalRenderer.h"

@interface AppDelegate()
{
    MetalView *mView;
    UIWindow *mWindow;
    UIViewController *mViewController;
//    MetalRenderer *mRenderer;
}

@end

@implementation AppDelegate

@synthesize window = mWindow;
@synthesize rootViewController = mViewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    // Init Engine
    AKUCoreCreate();
        
    NSUInteger width = 1280;
    NSUInteger height = 720;
    
    mView = [[MetalView alloc] initMetalViewWithWidth:width height:height];
        
    //    _renderer = [[MetalRenderer alloc] initWithMTKView:_view];
    //    _view.delegate = _renderer;
        
//        _viewController = [[NSViewController alloc] init];
//        _viewController.view = _view;
//
//    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
//
//    CGRect bounds = [[UIScreen mainScreen] bounds];
//    mView = [[MTKView alloc] initWithFrame:bounds device:device];
//
//    mRenderer = [[MetalRenderer alloc] initWithMTKView:mView];
//    mView.delegate = mRenderer;
    
    mViewController = [[UIViewController alloc] init];
    mViewController.view = mView;
    
    mWindow = [[UIWindow alloc] init];
    mWindow.rootViewController = mViewController;
    [mWindow makeKeyAndVisible];
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
