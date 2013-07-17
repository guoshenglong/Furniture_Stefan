//
//  RightDrawerViewController.m
//  Furniture0701
//
//  Created by 郭胜龙 on 13-7-15.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import "RightDrawerViewController.h"
#import "MMSideDrawerTableViewCell.h"

@interface RightDrawerViewController ()

@end

@implementation RightDrawerViewController

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
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    switch (section) {
        case DrawerSectionViewModels:
            return 4;
        case DrawerSectionRecentScan:
            return 4;
        default:
            return 0;
    }
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = (UITableViewCell*)[tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        
        cell = [[MMSideDrawerTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
        [cell setSelectionStyle:UITableViewCellSelectionStyleBlue];
    }
    
    switch (indexPath.section) {
        case DrawerSectionViewModels:{
            switch (indexPath.row) {
                case 0:
                    [cell.textLabel setText:@"清理缓存"];
                    break;
                case 1:
                    [cell.textLabel setText:@"重置模型"];
                    break;
                case 2:
                    [cell.textLabel setText:@"截屏"];
                    break;
                case 3:
                    [cell.textLabel setText:@"同步到云端"];
                    break;
                default:
                    break;
            }
        }
            
            break;
        case DrawerSectionRecentScan:{
            switch (indexPath.row) {
                case 0:
                    [cell.textLabel setText:@"QQ空间"];
                    break;
                case 1:
                    [cell.textLabel setText:@"新浪微博"];
                    break;
                case 2:
                    [cell.textLabel setText:@"腾讯微博"];
                    break;
                case 3:
                    [cell.textLabel setText:@"更多"];
                    break;
                    
                default:
                    break;
            }
        }
        default:
            break;
    }
    return cell;
}

- (NSString*)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    switch (section) {
        case DrawerSectionViewModels:
            return @"操作";
        case DrawerSectionRecentScan:
            return @"分享到";
        default:
            return nil;
    }
}


@end
