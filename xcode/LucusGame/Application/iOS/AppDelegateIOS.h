//
//  AppDelegate.h
//  LucusGame iOS
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#import <UIKit/UIKit.h>
#import <MetalKit/MetalKit.h>
#import "MetalRenderer.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    MTKView *mView;
    UIWindow *mWindow;
    UIViewController *mViewController;
    MetalRenderer *mRenderer;
}

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) UIViewController *rootViewController;
                        

@end

