//
//  LearnMoreViewController.m
//  Homepwner
//
//  Created by huzhengnan on 13-7-15.
//  Copyright (c) 2013年 huzhengnan. All rights reserved.
//

#import "LearnMoreViewController.h"
#import "SocietyViewController.h"

@interface LearnMoreViewController ()

@end

@implementation LearnMoreViewController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

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
    // 设置初始化不显示表格线
    [self tableView].separatorStyle = UITableViewCellSeparatorStyleNone;
    
    UIImage *baseImage = [UIImage imageNamed:@"navigator.png"];
    // UIImage *backgroundImage = [self scaleImage:baseImage toScale:1];
    [self.navigationController.navigationBar setBackgroundImage:baseImage forBarMetrics:UIBarMetricsDefault];
    // NSLog(@"LearnMoreTest--->>>>___>>>___>>>>%@", [self navigationController]);
    // 设置背景色为米白色
    [[self tableView] setBackgroundView:nil];
    [[self view] setBackgroundColor:[UIColor colorWithRed:(246.0/255.0) green:(244.0/255.0) blue:(235.0/255.0) alpha:1]];
    // 设置导航栏的一些内容
    UILabel *title = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 100, 44)];
    [title setText:@"设置"];
    [title setTextAlignment:NSTextAlignmentCenter];
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
    //[[self navigationItem] setLeftBarButtonItem:leftBarButton];
    
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
    UIBarButtonItem *rightBarButton = [[UIBarButtonItem alloc] initWithCustomView:rBackButton];
    // UIBarButtonItem *leftBarButton = [[UIBarButtonItem alloc] init];
    // [[self navigationItem] setRightBarButtonItem:rightBarButton];
    // 为视图添加uitableview

}

// 导航栏右侧按钮调用的方法
- (IBAction)rightButtonAction:(id)sender
{
    SocietyViewController *society = [[SocietyViewController alloc] init];
    [[self navigationController] pushViewController:society animated:YES];
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



#pragma mark - Table view data source

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if (section == 0) {
        return @"设定";
    } else if (section == 1) {
        return @"用户反馈";
    } else if (section == 2) {
        return @"程序信息";
    }else if (section == 3) {
        return @"应用推荐";
    }

}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
#warning Potentially incomplete method implementation.
    // Return the number of sections.
    return 4;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
#warning Incomplete method implementation.
    // Return the number of rows in the section.
    if (section == 0) {
        return 4;
    } else if (section == 1) {
        return 3;
    } else if (section == 2) {
        return 2;
    }else if (section == 3) {
        return 2;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
    }
    
    if (indexPath.section == 0) {
        if (indexPath.row == 0) {
            [[cell textLabel] setText:@"占用缓存：11.87M"];
            [[cell detailTextLabel] setText:@"点此清空缓存"];
        } else if (indexPath.row == 1) {
            [[cell textLabel] setText:@"显示未读提示"];
        }  else if (indexPath.row == 2) {
            [[cell textLabel] setText:@"清空收藏夹"];
        } else if (indexPath.row == 3) {
            [[cell textLabel] setText:@"登录账号"];
        }
    } else if (indexPath.section == 1) {
        if (indexPath.row == 0) {
            [[cell textLabel] setText:@"给我们提建议"];
            [cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
        }  else if (indexPath.row == 1) {
            [[cell textLabel] setText:@"评价我们，您的打分很重要"];
            [cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
        } else if (indexPath.row == 2) {
            [[cell textLabel] setText:@"推荐本应用给朋友"];
            [cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
        }
    } else if (indexPath.section == 2) {
        if (indexPath.row == 0) {
            [[cell textLabel] setText:@"版本号"];
            [[cell detailTextLabel] setText:@"alpha0.1"];
        }  else if (indexPath.row == 1) {
            [[cell textLabel] setText:@"版权"];
            [[cell detailTextLabel] setText:@"厦门飞特尔动漫创意有限公司"];
        }
    } else if (indexPath.section == 3) {
        if (indexPath.row == 0) {
            [[cell textLabel] setText:@"应用一"];
            [[cell detailTextLabel] setText:@"应用一描述"];
        }  else if (indexPath.row == 1) {
            [[cell textLabel] setText:@"应用二"];
            [[cell detailTextLabel] setText:@"应用二描述"];
        }
    }
    
    return cell;
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
    /*
     <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:@"<#Nib name#>" bundle:nil];
     // ...
     // Pass the selected object to the new view controller.
     [self.navigationController pushViewController:detailViewController animated:YES];
     */
}

@end
