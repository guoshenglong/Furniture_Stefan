    //
//  FirstViewController.m
//  LeveyTabBarDemo
//
//  Created by zhang on 12-10-10.
//  Copyright (c) 2012年 jclt. All rights reserved.
//
//

#import "FirstViewController.h"
#import "LeveyTabBarController.h"


@implementation FirstViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	//self.view.backgroundColor = [UIColor yellowColor];
    UIImageView *img=[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"bg.png"]];
    [self.view addSubview:img];
    
    [img release];
}

@end
