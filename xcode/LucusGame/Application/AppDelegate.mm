//
//  AppDelegate.m
//  LucusGame
//
//  Created by Alexander Kardakov on 13/02/2020.
//

#import "AppDelegate.h"

#include "host.h"
#include "modules.h"
#include "GameWorld.h"
#include "LucusMetalRenderSystem.h"
#include "LucusMetalWindow.h"

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
    
    AKUChangeWorkingDir([[[NSBundle mainBundle] resourcePath] UTF8String]);
    
    NSUInteger width = 1280;
    NSUInteger height = 720;
    
    CGRect frame = CGRectMake(0, 0, width, height);
    RootView = [[NSView alloc] initWithFrame:frame];
    
    RootVC = [[NSViewController alloc] init];
    RootVC.view = RootView;
    
    Window = [NSWindow windowWithContentViewController:RootVC];
    Window.title = @"Lucus Game";
    [Window makeKeyAndOrderFront:self];
    
    // Create Metal Render System
    LucusEngine::MetalRenderSystem* renderSystem = new LucusEngine::MetalRenderSystem();
    
    // Create Window
    LucusEngine::RenderWindow* window = renderSystem->CreateRenderWindow((u32)width, (u32)height);
    LucusEngine::MetalWindow* metalWindow = static_cast<LucusEngine::MetalWindow*>(window);
//    metalWindow->SetWindow();
    
    [RootView addSubview:metalWindow->mView];
    
    // Setup RenderSystem
    AKUSetRenderSystem(static_cast<LucusEngine::RenderSystem*>(renderSystem));
    
    // Start Loop
//    AKUStartCoreLoop();
    AKUCreateWorld(new GameWorld());
//    AKURun();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    AKUCoreDestroy();
    return YES;
}

#endif

@end
