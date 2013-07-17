//
//  DetialViewController.m
//  Homepwner
//
//  Created by huzhengnan on 13-7-9.
//  Copyright (c) 2013年 huzhengnan. All rights reserved.
//

#import "DetialViewController.h"
#import "BNRItem.h"
#import "SameKindViewController.h"

@implementation DetialViewController
- (void) viewDidLoad
{
    [super viewDidLoad];
    // [[self view] setBackgroundColor:[UIColor groupTableViewBackgroundColor]];
    // [[self tableView] setBackgroundColor:[UIColor blackColor]];
    UIImage *baseImage = [UIImage imageNamed:@"navigator.png"];
    // UIImage *backgroundImage = [self scaleImage:baseImage toScale:1];
    [self.navigationController.navigationBar setBackgroundImage:baseImage forBarMetrics:UIBarMetricsDefault];
    
    [[self view] setBackgroundColor:[UIColor colorWithRed:(246.0/255.0) green:(244.0/255.0) blue:(235.0/255.0) alpha:1]];
    UILabel *title = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 100, 44)];
    [title setText:@"手机淘宝网"];
    [title setTextAlignment:UITextAlignmentCenter];
    [title setFont:[UIFont boldSystemFontOfSize:20]];
    [title setTextColor:[UIColor colorWithRed:(140.0/255.0) green:(116.0/255.0) blue:(50.0/255.0) alpha:1]];
    [title setBackgroundColor:[UIColor clearColor]];
    [[self navigationItem] setTitleView:title];
    
    // 设置自定义返回按钮
    CGRect backframe = CGRectMake(0, 0, 54, 30);
    UIButton *backButton = [[UIButton alloc] initWithFrame:backframe];
    UIImage *backImage = [UIImage imageNamed:@"back.png"];
    UIImage *backImage_black = [UIImage imageNamed:@"back_black.png"];
    [backButton setBackgroundImage:backImage forState:UIControlStateNormal];
    [backButton setBackgroundImage:backImage_black forState:UIControlStateHighlighted];
    // [backButton setTitle:@"返回" forState:UIControlStateNormal];
    backButton.titleLabel.font = [UIFont systemFontOfSize:13];
    [backButton addTarget:self action:@selector(doClickBackAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *leftBarButton = [[UIBarButtonItem alloc] initWithCustomView:backButton];
    // UIBarButtonItem *leftBarButton = [[UIBarButtonItem alloc] init];
    [[self navigationItem] setLeftBarButtonItem:leftBarButton];
    
    // 自定义右侧按钮
    UIImage *mabyLike = [UIImage imageNamed:@"mabyLike"];
    UIImage *mabyLike_black = [UIImage imageNamed:@"mabyLike_black"];

    CGRect rBackframe = CGRectMake(0, 0, 55, 32);
    UIButton *rBackButton = [[UIButton alloc] initWithFrame:rBackframe];
    // 设置按钮发光
    // rBackButton.showsTouchWhenHighlighted = YES;
    [rBackButton setBackgroundImage:mabyLike forState:UIControlStateNormal];
    [rBackButton setBackgroundImage:mabyLike_black forState:UIControlStateHighlighted];
    // [rBackButton setTitle:@"猜你喜欢" forState:UIControlStateNormal];
    rBackButton.titleLabel.font = [UIFont systemFontOfSize:13];
    [rBackButton addTarget:self action:@selector(rightButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *rightBarButton = [[UIBarButtonItem alloc] initWithCustomView:rBackButton];
    // UIBarButtonItem *leftBarButton = [[UIBarButtonItem alloc] init];
    
    [[self navigationItem] setRightBarButtonItem:rightBarButton];
}

// 返回上级菜单页面
- (IBAction)doClickBackAction:(id)sender
{
    [[self navigationController] popViewControllerAnimated:YES];
}

- (IBAction)rightButtonAction:(id)sender
{
    SameKindViewController *sameKindViewController = [[SameKindViewController alloc] init];
    [[self navigationController] pushViewController:sameKindViewController animated:YES];
}
@end
