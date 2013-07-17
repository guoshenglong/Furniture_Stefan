    //
//  SecondViewController.m
//  LeveyTabBarDemo
//
//  Created by zhang on 12-10-10.
//  Copyright (c) 2012年 jclt. All rights reserved.
//
//

#import "LeveyTabBarDemoAppDelegate.h"
#import "SecondViewController.h"
#import "LeveyTabBarController.h"
#import "FirstViewController.h"

@implementation SecondViewController


- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];

}

- (void)viewDidLoad
{
    [super viewDidLoad];
	self.view.backgroundColor = [UIColor redColor];
	
	UIBarButtonItem *rightBtn = [[UIBarButtonItem alloc] initWithTitle:@"Add" style:UIBarButtonItemStyleBordered target:self action:@selector(hide)];
	self.navigationItem.rightBarButtonItem = rightBtn;
	[rightBtn release];
	
}


- (void)hide
{
    static NSInteger dir = 0;
    
    FirstViewController *firstVC = [[FirstViewController alloc] init];
    
    //firstVC.hidesBottomBarWhenPushed = YES;
    LeveyTabBarDemoAppDelegate* appDelegate = (LeveyTabBarDemoAppDelegate*)[UIApplication sharedApplication].delegate;

    dir++;
    appDelegate.leveyTabBarController.animateDriect = dir % 2;
    firstVC.hidesBottomBarWhenPushed = YES;
    //[appDelegate.leveyTabBarController hidesTabBar:YES animated:YES]; 
    [self.navigationController pushViewController:firstVC animated:YES];
    [firstVC release];
}


- (void)dealloc {
    [super dealloc];
}


@end
