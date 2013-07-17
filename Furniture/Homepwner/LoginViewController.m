//
//  LoginViewController.m
//  Homepwner
//
//  Created by huzhengnan on 13-7-16.
//  Copyright (c) 2013年 huzhengnan. All rights reserved.
//

#import "LoginViewController.h"

@interface LoginViewController ()

@end

@implementation LoginViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // 隐藏导航栏
    [self navigationController].navigationBarHidden = YES;
    [self setHidesBottomBarWhenPushed:YES];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)closeButtonAction:(id)sender
{
    [self navigationController].navigationBarHidden = NO;
    [[self navigationController] popViewControllerAnimated:NO];
}

@end
