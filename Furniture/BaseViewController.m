//
//  BaseViewController.m
//  LBShopMall
//
//  Created by 李成武 on 13-3-22.
//  Copyright (c) 2013年 联龙博通在线服务中心.李成武. All rights reserved.
//

#import "BaseViewController.h"
#import "CommonHelper.h"
#import "WaitView.h"

#define kButtonShareTag 500//分享
#define kButtonBackTag 501//返回
#define kButtoSearchTag 502//搜索
#define kButtonNetSettingTag 503 //网络设置按钮

@interface BaseViewController ()

@property(nonatomic,retain)WaitView *loadingView;
@property (nonatomic,retain)UIImageView *bgImageView;
@property(nonatomic,retain)UIView *errorView;

@end

@implementation BaseViewController

@synthesize loadingView;
@synthesize errorView;
@synthesize bgImageView = _bgImageView;

- (void)dealloc {
    
    self.loadingView.delegate=nil;
    self.loadingView=nil;
    self.errorView=nil;
    self.bgImageView = nil;
    //[super dealloc];
}
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        UIImage *baseImage = [UIImage imageNamed:@"navigator.png"];
        // UIImage *backgroundImage = [self scaleImage:baseImage toScale:1];
        
        [self.navigationController.navigationBar setBackgroundImage:baseImage forBarMetrics:UIBarMetricsDefault];
        NSLog(@"nav:%@", self.navigationController);
        NSLog(@"BaseView ------ huzhengnan光荣地出现在BaseView");

    }
    return self;
}

- (void)loadView{
    [super loadView];
    
    
    self.loadingView = [[WaitView alloc] init];
    self.loadingView .frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
    [self.loadingView setDelegate:self];
    [self.view addSubview:self.loadingView ];
    self.loadingView .hidden = YES;
    
    
    
    //加载失败图
    errorView=[[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    [errorView setBackgroundColor:[UIColor colorWithPatternImage:[UIImage imageNamed:@"background.png"]]];
    [errorView setHidden:YES];
    [self.view addSubview:errorView];
    
    UITapGestureRecognizer *errorTap=[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(errorViewTappedGesture:)];
    [errorTap setDelegate:self];
    [errorView addGestureRecognizer:errorTap];
    
    
    UIImageView *errorImgView=[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"NoNetwork.png"]];
    [errorImgView setFrame:CGRectMake((320-115)/2, 85, 115, 133)];
    [errorView addSubview:errorImgView];
    
    
    UIButton *btnSetting=[UIButton buttonWithType:UIButtonTypeCustom];
    [btnSetting setTag:kButtonNetSettingTag];
    [btnSetting setFrame:CGRectMake((320-88)/2, 310, 88, 12)];
    [btnSetting setBackgroundImage:[UIImage imageNamed:@"setNetwork.png"] forState:UIControlStateNormal];
    [btnSetting addTarget:self action:@selector(baseButtonClick:) forControlEvents:UIControlEventTouchUpInside];
    [errorView addSubview:btnSetting];
    
}
- (void)viewDidLoad
{
    [super viewDidLoad];
    [self.view setBackgroundColor:[UIColor colorWithRed:242/255.0f green:242/255.0f blue:246/255.0f alpha:1.0f]];
    
    UIImage *baseImage = [UIImage imageNamed:@"navigator.png"];
    // UIImage *backgroundImage = [self scaleImage:baseImage toScale:1];
    [self.navigationController.navigationBar setBackgroundImage:baseImage forBarMetrics:UIBarMetricsDefault];
//    [self showLoadingView];

	// Do any additional setup after loading the view.
    
   
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - GEsturesDelegate
-(BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
{
    if([touch.view isKindOfClass:[UIButton class]])
    {
        return NO;
    }
    return YES;
}

#pragma mark - waitView delegate
-(void)waitViewTap:(NSString *)url
{
    [self errorViewTappedGesture:nil];   
}

#pragma mark - private method

-(void)showLoadingView
{
    [self.view bringSubviewToFront:loadingView];
    [loadingView setHidden:NO];
}

-(void)hideLoadingView
{
    //终止风火轮和隐藏
    [loadingView setTitleText:@"" url:nil];
    [loadingView setHidden:YES];
}

-(void)errorViewTappedGesture:(UITapGestureRecognizer *)gesture
{
    [errorView setHidden:YES];
    [self showLoadingView];
}

-(void)showErrorView
{   
    [loadingView setTitleText:nil];
//    [self.view bringSubviewToFront:loadingView];
}

- (void)showTitle : (NSString *)title{
    UILabel *lable = [[UILabel alloc] init];
    lable.text = title;
    lable.frame = CGRectMake(110, 10, 100, 24);
//    lable.font = [UIFont fontWithName:kFontMSYaHei size:20];
    lable.backgroundColor = [UIColor clearColor];
    lable.textAlignment = UITextAlignmentCenter;
    lable.textColor = [UIColor whiteColor];
    self.navigationItem.titleView = lable;
    
}

-(void)showSearchBar
{
    UIButton *btnSearch = [UIButton buttonWithType:UIButtonTypeCustom];
    [btnSearch setTag:kButtoSearchTag];
    [btnSearch setFrame:CGRectMake(0, 0, 54, 47)];
    [btnSearch addTarget:self action:@selector(baseButtonClick:) forControlEvents:UIControlEventTouchUpInside];
    [btnSearch setBackgroundImage:[UIImage imageNamed:@"search_button.png"] forState:UIControlStateNormal];
    
    UIBarButtonItem *rightBar = [[UIBarButtonItem alloc] initWithCustomView:btnSearch];
    self.navigationItem.rightBarButtonItem = rightBar;
    
}

-(void)showShareBar
{
    //分享
    UIButton *btnShare = [UIButton buttonWithType:UIButtonTypeCustom];
    [btnShare setTag:kButtonShareTag];
    [btnShare setFrame:CGRectMake(0, 0, 54, 47)];
    [btnShare addTarget:self action:@selector(baseButtonClick:) forControlEvents:UIControlEventTouchUpInside];
    [btnShare setBackgroundImage:[UIImage imageNamed:@"Share.png"] forState:UIControlStateNormal];
    
    UIBarButtonItem *rightBar = [[UIBarButtonItem alloc] initWithCustomView:btnShare];
    self.navigationItem.rightBarButtonItem = rightBar;
    
}

-(void)showBackBar
{
    //返回按钮
    UIButton *backButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [backButton setTag:kButtonBackTag];
    [backButton setFrame:CGRectMake(0, 7, 48, 30)];
    [backButton addTarget:self action:@selector(baseButtonClick:) forControlEvents:UIControlEventTouchUpInside];
    [backButton setBackgroundImage:[UIImage imageNamed:@"nav_back.png"] forState:UIControlStateNormal];
    [backButton setBackgroundImage:[UIImage imageNamed:@"nav_back_pressed.png"] forState:UIControlStateHighlighted];
    
    UIBarButtonItem *leftBar = [[UIBarButtonItem alloc] initWithCustomView:backButton];
    self.navigationItem.leftBarButtonItem = leftBar;
   
}

-(void)baseButtonClick:(UIButton *)btn
{
    switch (btn.tag) {
        case kButtonNetSettingTag:
        {
            //IOS5.1+之后就不行了
            if([[[UIDevice currentDevice] systemVersion] floatValue]>5.1)
            {
                [CommonHelper showAlert:nil msg:@"您可以按照一下方案开启网络\n1.设置=》无线局域网\n2.设置=》通用=》蜂窝移动网络"];
            }
            else {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"prefs:root=General&path=Network"]];
            }
            NSLog(@"231");
        }
            break;
        case kButtonBackTag:
        {
            [self.navigationController popViewControllerAnimated:YES];
        }
            break;
        case kButtonShareTag:
        {}
            break;
        case kButtoSearchTag:
        {}
            break;
        default:
            break;
    }
}

-(void)showImageName:(NSString *)name  isShow :(BOOL)animaed{
    
    [self.view bringSubviewToFront:self.bgImageView];
    self.bgImageView.image = [UIImage imageNamed:name];
    self.bgImageView.hidden = !animaed;
    
}

@end
