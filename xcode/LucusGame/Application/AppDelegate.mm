//
//  AppDelegate.m
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#import "AppDelegate.h"

#include "host.h"
#include "modules.h"

static AppDelegate* mInstance = nil;

@implementation AppDelegate

+ (nullable AppDelegate*)sharedDelegate
{
    return mInstance;
}

- (nonnull instancetype)init
{
    self = [super init];
    mInstance = self;
    return self;
}

- (void)dealloc
{
    mInstance = nil;
}

#if defined(TARGET_IOS)
@synthesize Window;
@synthesize RootVC;
@synthesize RootView;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Init Engine
    AKUCoreCreate();
    
    CGRect frame = [[UIScreen mainScreen] bounds];
    
    RootView = [[UIView alloc] initWithFrame:frame];
    
    RootVC = [[UIViewController alloc] init];
    RootVC.view = RootView;
    
    Window = [[UIWindow alloc] init];
    Window.rootViewController = RootVC;
    [Window makeKeyAndVisible];
    
    // Create MetalView
    // Setup RenderSystem
    
    return YES;
}

#elif defined(TARGET_OSX)
@synthesize Window;
@synthesize RootVC;
@synthesize RootView;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Init Engine
    AKUCoreCreate();
    
    // Init Modules
    AKUModulesCreate();
    
    // Set Working Dir
    AKUChangeWorkingDir([[[NSBundle mainBundle] resourcePath] UTF8String]);
    
    // Create & Run Lua
    AKUCreateLua();
    
    u32 width, height;
    AKUGetApplicationSize(width, height);
    
    CGRect frame = CGRectMake(0, 0, width, height);
    RootView = [[NSView alloc] initWithFrame:frame];
    
    RootVC = [[NSViewController alloc] init];
    RootVC.view = RootView;
    
    std::string title;
    AKUGetApplicationTitle(title);
    
    Window = [NSWindow windowWithContentViewController:RootVC];
    Window.title = [NSString stringWithUTF8String:title.c_str()];
    [Window makeKeyAndOrderFront:self];
    
    // Create Metal Render System
    AKUCreateRenderSystem(width, height);
    // Create World
//    AKUCreateWorld();
    
    // Init game and start loop
    AKURun();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    AKUCoreDestroy();
    return YES;
}

#endif

@end
