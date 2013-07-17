//
//  SameKindViewController.m
//  Homepwner
//
//  Created by huzhengnan on 13-7-15.
//  Copyright (c) 2013年 huzhengnan. All rights reserved.
//

#import "SameKindViewController.h"
#import "ItemsViewController.h"
#import "BNRItemStore.h"
#import "BNRItem.h"
#import "HomepwnerItemCell.h"
#import "LearnMoreViewController.h"
#import "CKRefreshControl.h"
#import <CoreText/CoreText.h>
#import "Detial2ViewController.h"

@interface SameKindViewController ()

@end

@implementation SameKindViewController
- (id)init
{
    // 调用父类的指定初始化方法
    self = [super initWithStyle:UITableViewStyleGrouped];
    if (self) {
        for (int i = 0; i < 5; i++) {
            [[BNRItemStore sharedStore] createItem];
        }
        // UINavigationItem *n = [self navigationItem];
        // [n setTitle:@"Homepwer"];
        
        // 创建新的UIBarButtonItem对象
        // 将其目标对象设置为当前对象，将其动作方法设置为addNewItem
        /*
         UIButton *bb = [UIButton buttonWithType:UIButtonTypeCustom];
         [bb setBackgroundImage:[UIImage imageNamed:@"L2utton.png"] forState:UIControlStateNormal];
         UIBarButtonItem *bbl = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(leftButtonAction:)];
         UIBarButtonItem *bbr = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(rightButtonAction:)];
         UIImage *lbackgroundImage = [UIImage imageNamed:@"L2utton.png"];
         // UIImage *rbackgroundImage = [UIImage imageNamed:@"Rbutton.png"];
         UIImage *tempImage = [self scaleImage:lbackgroundImage toScale:0.5];
         // 图片显示问题，暂时先用透明图片代替
         [bbl setBackgroundImage:lbackgroundImage forState:UIControlStateNormal barMetrics:UIBarMetricsDefault];
         [bbr setBackgroundImage:lbackgroundImage forState:UIControlStateNormal barMetrics:UIBarMetricsDefault];
         UIBarButtonItem *bbi = [[UIBarButtonItem alloc] initWithCustomView:bb];
         [[self navigationItem] setLeftBarButtonItem:bbi];
         [[self navigationItem] setTitle:@"我的收藏"];
         // [[self navigationItem] setLeftBarButtonItem:[self editButtonItem]];
         [[self navigationItem] setRightBarButtonItem:bbr];
         **/
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
        // UIImage *rBackImage = [UIImage imageNamed:@"RButton"];
        CGRect rBackframe = CGRectMake(0, 0, 25, 25);
        UIButton *rBackButton = [UIButton buttonWithType:UIButtonTypeInfoDark];
        rBackButton.frame = rBackframe;
        // 设置按钮发光
        // rBackButton.showsTouchWhenHighlighted = YES;
        // [rBackButton setBackgroundImage:rBackImage forState:UIControlStateNormal];
        // [rBackButton setTitle:@"返回" forState:UIControlStateNormal];
        rBackButton.titleLabel.font = [UIFont systemFontOfSize:13];
        [rBackButton addTarget:self action:@selector(rightButtonAction:) forControlEvents:UIControlEventTouchUpInside];
        UIBarButtonItem *rightBarButton = [[UIBarButtonItem alloc] initWithCustomView:rBackButton];
        // UIBarButtonItem *leftBarButton = [[UIBarButtonItem alloc] init];
        // [[self navigationItem] setRightBarButtonItem:rightBarButton];
        
        // 设置导航条属性
        UILabel *title = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 100, 44)];
        [title setText:@"同类产品"];
        [title setTextAlignment:UITextAlignmentCenter];
        [title setFont:[UIFont boldSystemFontOfSize:20]];
        [title setTextColor:[UIColor colorWithRed:(140.0/255.0) green:(116.0/255.0) blue:(50.0/255.0) alpha:1]];
        [title setBackgroundColor:[UIColor clearColor]];
        [[self navigationItem] setTitleView:title];
        // [[self navigationItem] setTitle:@"我的收藏"];
        
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    UINib *nib = [UINib nibWithNibName:@"HomepwnerItemCell" bundle:nil];
    UIImage *baseImage = [UIImage imageNamed:@"navigator.png"];
    [self tableView].separatorStyle = UITableViewCellSeparatorStyleNone;
    // UIImage *backgroundImage = [self scaleImage:baseImage toScale:1];
    [self.navigationController.navigationBar setBackgroundImage:baseImage forBarMetrics:UIBarMetricsDefault];
    [[self tableView] registerNib:nib forCellReuseIdentifier:@"HomepwnerItemCell"];
    NSLog(@"此处设置背景颜色");
    [[self view] setBackgroundColor:[UIColor colorWithRed:(246.0/255.0) green:(244.0/255.0) blue:(235.0/255.0) alpha:1]];
    [[self tableView] setBackgroundColor:[UIColor colorWithRed:(246.0/255.0) green:(244.0/255.0) blue:(235.0/255.0) alpha:1]];
    [[self tableView] setBackgroundView:nil];
    // 设置水滴下拉刷新刷新
    if ([[UIDevice currentDevice].systemVersion floatValue] < 6.0) {
        CKRefreshControl *refreshControl = [CKRefreshControl new];
        // self.refreshControl = (id)refreshControl;
    } else {
        // self.refreshControl = [[UIRefreshControl alloc] init];
    }
    // self.refreshControl.tintColor = [UIColor orangeColor];
    NSLog(@"version is %f", [[UIDevice currentDevice].systemVersion floatValue]);
    self.refreshControl.attributedTitle = [[NSAttributedString alloc] initWithString:@"下拉刷新"];
    [self.refreshControl addTarget:self action:@selector(doRefresh:) forControlEvents:UIControlEventValueChanged];
}

// 实现下拉刷新的几个方法
- (void)doRefresh:(id)sender{
    NSLog(@"refreshing");
    self.refreshControl.attributedTitle = [[NSAttributedString alloc] initWithString:@"刷新中"];
    [self performSelector:@selector(endRefreshing) withObject:nil afterDelay:2];
    // [self.refreshControl addTarget:self action:@selector(endRefreshing:) forControlEvents:UIControlEventValueChanged];
}

- (void)endRefreshing
{
    NSLog(@"refreshed");
    [self.refreshControl endRefreshing];
    self.refreshControl.attributedTitle = [[NSAttributedString alloc] initWithString:@"下拉刷新"];
    [self.tableView reloadData];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (IBAction)doClickBackAction:(id)sender
{
    [[self navigationController] popViewControllerAnimated:YES];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}


// 的比例缩放图片大小的函数，但是不知道怎么的显示出来是个白色
- (UIImage *)scaleImage:(UIImage *)image toScale:(float)scaleSize
{
    UIGraphicsBeginImageContext(CGSizeMake(image.size.width * scaleSize, image.size.height * scaleSize));
    UIImage *scaledImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return scaledImage;
}

- (id)initWithStyle:(UITableViewStyle)style
{
    return [self init];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [[[BNRItemStore sharedStore] allItems] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    // 创建UITableViewCell对象
    // UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"UITableViewCell"];
    // 检查是否有可以重用的cell
    //UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"UITableView"];
    
    //if (!cell) {
    //    cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"UITableViewCell"];
    // }
    
    
    // 获取allItems的第N个BNRItem实例
    BNRItem *p = [[[BNRItemStore sharedStore] allItems] objectAtIndex:[indexPath row]];
    HomepwnerItemCell *cell = [tableView dequeueReusableCellWithIdentifier:@"HomepwnerItemCell"];
    // [[cell textLabel] setText:[p description]];
    [cell setBackgroundColor:[UIColor colorWithRed:(246.0/255.0) green:(244.0/255.0) blue:(235.0/255.0) alpha:1]];
    [cell setBackgroundView:[[UIView alloc] initWithFrame:CGRectZero]];
    [[cell centerImage] setImage:[UIImage imageNamed:[p imagePath]]];
    [[cell name] setText:[p itemName]];
    [[cell describe] setText:[p describe]];
    [[cell price] setText:[p price]];
    // [cell setSelectionStyle:UITableViewCellEditingStyleNone];
    return  cell;
}

- (IBAction)leftButtonAction:(id)sender
{
    /*// int lastRow = [[self tableView] numberOfRowsInSection:0];
     BNRItem *newItem = [[BNRItemStore sharedStore] createItem];
     int lastRow = [[[BNRItemStore sharedStore] allItems] indexOfObject:newItem];
     NSIndexPath *ip = [NSIndexPath indexPathForRow:lastRow inSection:0];
     [[self tableView] insertRowsAtIndexPaths:[NSArray arrayWithObject:ip] withRowAnimation:UITableViewRowAnimationTop];*/
    UIActionSheet *functionList = [[UIActionSheet alloc] initWithTitle:nil delegate:self cancelButtonTitle:@"取消" destructiveButtonTitle:nil otherButtonTitles:@"上电脑看自己的收藏", @"同步收藏夹", nil];
    [functionList setActionSheetStyle:UIActionSheetStyleBlackTranslucent];
    [functionList showInView:self.view.window];
}

- (IBAction)rightButtonAction:(id)sender
{
    LearnMoreViewController *learnMore = [[LearnMoreViewController alloc] init];
    [[self navigationController] pushViewController:learnMore animated:YES];
}

// - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
// {
//  if (editingStyle == UITableViewCellEditingStyleDelete) {
//   BNRItemStore *ps = [BNRItemStore sharedStore];
// NSArray *items = [ps allItems];
// BNRItem *p = [items objectAtIndex:[indexPath row]];
// [ps removeItem:p];
// [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
// }
// }

- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath
{
    [[BNRItemStore sharedStore] moveItemAtIndex:[sourceIndexPath row] toIndex:[destinationIndexPath row]];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    Detial2ViewController *detail2ViewController = [[Detial2ViewController alloc] init];
    [[self navigationController] pushViewController:detail2ViewController animated:YES];
}
- (float)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 130;
}
@end
