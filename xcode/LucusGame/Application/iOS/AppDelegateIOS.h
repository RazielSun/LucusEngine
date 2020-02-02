//
//  AppDelegate.h
//  LucusGame iOS
//
//  Created by Alexander Kardakov on 02/02/2020.
//

#import <UIKit/UIKit.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    UIView* mView;
    UIWindow *mWindow;
    UIViewController *mViewController;
}

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) UIViewController *rootViewController;
                        

@end

