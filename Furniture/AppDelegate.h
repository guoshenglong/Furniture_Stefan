//
//  AppDelegate.h
//  Furniture0701
//
//  Created by 郭胜龙 on 13-7-1.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ViewController;
@class LeveyTabBarController;
@interface AppDelegate : UIResponder <UIApplicationDelegate, UINavigationControllerDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) ViewController *viewController;

@property (nonatomic, retain) IBOutlet LeveyTabBarController *leveyTabBarController;

@end
