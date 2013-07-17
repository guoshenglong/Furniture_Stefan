//
//  SocietyViewController.m
//  Homepwner
//
//  Created by huzhengnan on 13-7-11.
//  Copyright (c) 2013年 huzhengnan. All rights reserved.
//

#import "SocietyViewController.h"

@interface SocietyViewController ()

@end

@implementation SocietyViewController

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
    [[self view] setBackgroundColor:[UIColor groupTableViewBackgroundColor]];
    UILabel *title = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 100, 44)];
    [title setText:@"好友动态"];
    [title setTextAlignment:UITextAlignmentCenter];
    [title setFont:[UIFont boldSystemFontOfSize:20]];
    [title setTextColor:[UIColor colorWithRed:(140.0/255.0) green:(116.0/255.0) blue:(50.0/255.0) alpha:1]];
    [title setBackgroundColor:[UIColor clearColor]];
    [[self navigationItem] setTitleView:title];
    
    // 设置自定义返回按钮
    UIImage *backImage = [UIImage imageNamed:@""];
    CGRect backframe = CGRectMake(0, 0, 54, 30);
    UIButton *backButton = [[UIButton alloc] initWithFrame:backframe];
    [backButton setBackgroundImage:backImage forState:UIControlStateNormal];
    [backButton setTitle:@"返回" forState:UIControlStateNormal];
    backButton.titleLabel.font = [UIFont systemFontOfSize:13];
    [backButton addTarget:self action:@selector(doClickBackAction:) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *leftBarButton = [[UIBarButtonItem alloc] initWithCustomView:backButton];
    // UIBarButtonItem *leftBarButton = [[UIBarButtonItem alloc] init];
    [[self navigationItem] setLeftBarButtonItem:leftBarButton];
    
    // 设置导航栏右边的按钮，用于显示社交分享
    // 自定义右侧按钮
    UIImage *rBackImage = [UIImage imageNamed:@"RButton"];
    CGRect rBackframe = CGRectMake(0, 0, 25, 25);
    UIButton *rBackButton = [[UIButton alloc] initWithFrame:rBackframe];
    // 设置按钮发光
    rBackButton.showsTouchWhenHighlighted = YES;
    [rBackButton setBackgroundImage:rBackImage forState:UIControlStateNormal];
    // [rBackButton setTitle:@"返回" forState:UIControlStateNormal];
    rBackButton.titleLabel.font = [UIFont systemFontOfSize:13];
    [rBackButton addTarget:self action:@selector(rightButtonAction:) forControlEvents:UIControlEventTouchUpInside];
    // UIBarButtonItem *rightBarButton = [[UIBarButtonItem alloc] initWithCustomView:rBackButton];
    UIBarButtonItem *rightBarButton = [[UIBarButtonItem  alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCamera target:self action:nil];
    // UIBarButtonItem *leftBarButton = [[UIBarButtonItem alloc] init];
    [[self navigationItem] setRightBarButtonItem:rightBarButton];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)doClickBackAction:(id)sender
{
    [[self navigationController] popViewControllerAnimated:YES];
}
@end
