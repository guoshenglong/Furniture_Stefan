//
//  AppDelegate.m
//  Furniture0701
//
//  Created by 郭胜龙 on 13-7-1.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import "AppDelegate.h"

#import "ViewController.h"
#import "LeveyTabBarController.h"

#import "MMDrawerController.h"
#import "CateViewController.h"

#import "ItemsViewController.h"

#import "LeftSideDrawerViewController.h"
#import "RightDrawerViewController.h"
#import "LearnMoreViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        self.viewController = [[ViewController alloc] initWithNibName:@"ViewController_iPhone" bundle:nil];
    } else {
        self.viewController = [[ViewController alloc] initWithNibName:@"ViewController_iPad" bundle:nil];
    }
    
    //加载抽屉视图
    
    //LeftViewController * leftDrawer = [[LeftViewController alloc] init];
    LeftSideDrawerViewController * leftDrawer = [[LeftSideDrawerViewController alloc]init];
    leftDrawer.view.backgroundColor = [UIColor blackColor];

    RightDrawerViewController *rightDrawer = [[RightDrawerViewController alloc] init];
    MMDrawerController * drawerController = [[MMDrawerController alloc]
                                             initWithCenterViewController:self.viewController
                                             leftDrawerViewController:leftDrawer
                                             rightDrawerViewController:rightDrawer];
    
    [drawerController setMaximumRightDrawerWidth:140];
    [drawerController setMaximumLeftDrawerWidth:180];
    
    [drawerController setOpenDrawerGestureModeMask:MMOpenDrawerGestureModeBezelPanningCenterView];
    [drawerController setCloseDrawerGestureModeMask:MMCloseDrawerGestureModeAll];
    
    //胡正楠版本
    // 创建ItemsViewController对象
    ItemsViewController *itemsViewController = [[ItemsViewController alloc] init];
    
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:itemsViewController];
    
    //自己添加的
    // CateViewController *thirdVC = [[CateViewController alloc] init];
    CateViewController *thirdVC = [[CateViewController alloc]initWithNibName:@"CateViewController" bundle:[NSBundle mainBundle]];
    [[thirdVC view]setBackgroundColor:[UIColor whiteColor]];
    
    //导航视图加载
    UINavigationController *navigation = [[UINavigationController alloc]initWithRootViewController:thirdVC];
    // NSLog(@"导航条%@", [thirdVC ])
    UIImage *baseImage = [UIImage imageNamed:@"navigator.png"];
    // UIImage *backgroundImage = [self scaleImage:baseImage toScale:1];
    [thirdVC.navigationController.navigationBar setBackgroundImage:baseImage forBarMetrics:UIBarMetricsDefault];
    
    
	LearnMoreViewController *fourthVC = [[LearnMoreViewController alloc] init];

    UINavigationController *navController_learnMore = [[UINavigationController alloc] initWithRootViewController:fourthVC];
    
	NSArray *ctrlArr = [NSArray arrayWithObjects:drawerController, navigation,navController,navController_learnMore,nil];

    
	NSMutableDictionary *imgDic = [NSMutableDictionary dictionaryWithCapacity:3];
	[imgDic setObject:[UIImage imageNamed:@"01.png"] forKey:@"Default"];
	[imgDic setObject:[UIImage imageNamed:@"01_selected.png"] forKey:@"Highlighted"];
	[imgDic setObject:[UIImage imageNamed:@"01_selected.png"] forKey:@"Seleted"];
	NSMutableDictionary *imgDic2 = [NSMutableDictionary dictionaryWithCapacity:3];
	[imgDic2 setObject:[UIImage imageNamed:@"02.png"] forKey:@"Default"];
	[imgDic2 setObject:[UIImage imageNamed:@"02_selected.png"] forKey:@"Highlighted"];
	[imgDic2 setObject:[UIImage imageNamed:@"02_selected.png"] forKey:@"Seleted"];
	NSMutableDictionary *imgDic3 = [NSMutableDictionary dictionaryWithCapacity:3];
	[imgDic3 setObject:[UIImage imageNamed:@"03.png"] forKey:@"Default"];
	[imgDic3 setObject:[UIImage imageNamed:@"03_selected.png"] forKey:@"Highlighted"];
	[imgDic3 setObject:[UIImage imageNamed:@"03_selected.png"] forKey:@"Seleted"];
	NSMutableDictionary *imgDic4 = [NSMutableDictionary dictionaryWithCapacity:3];
	[imgDic4 setObject:[UIImage imageNamed:@"04.png"] forKey:@"Default"];
	[imgDic4 setObject:[UIImage imageNamed:@"04_selected.png"] forKey:@"Highlighted"];
	[imgDic4 setObject:[UIImage imageNamed:@"04_selected.png"] forKey:@"Seleted"];
    //	NSMutableDictionary *imgDic5 = [NSMutableDictionary dictionaryWithCapacity:3];
    //	[imgDic5 setObject:[UIImage imageNamed:@"1.png"] forKey:@"Default"];
    //	[imgDic5 setObject:[UIImage imageNamed:@"2.png"] forKey:@"Highlighted"];
    //	[imgDic5 setObject:[UIImage imageNamed:@"2.png"] forKey:@"Seleted"];
	
	NSArray *imgArr = [NSArray arrayWithObjects:imgDic,imgDic2,imgDic3,imgDic4,nil];
	
	LeveyTabBarController *leveyTabBarController = [[LeveyTabBarController alloc] initWithViewControllers:ctrlArr imageArray:imgArr];
	[leveyTabBarController.tabBar setBackgroundImage:[UIImage imageNamed:@"toolbarBackground.png"]];
	[leveyTabBarController setTabBarTransparent:NO];
	//[self.window addSubview:leveyTabBarController.view];
    //self.window.rootViewController = self.viewController;
    
    
    

    self.window.rootViewController = leveyTabBarController;
   [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
