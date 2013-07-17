//
//  LeftSideDrawerViewController.m
//  Furniture0701
//
//  Created by 郭胜龙 on 13-7-15.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import "LeftSideDrawerViewController.h"
#import "MMSideDrawerTableViewCell.h"

@interface LeftSideDrawerViewController ()

@end

@implementation LeftSideDrawerViewController

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
                    [cell.textLabel setText:@"美式椅子"];
                    cell.imageView.image = [UIImage imageNamed:@"studyroom_chair.png"];
                    [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                    break;
                case 1:
                    [cell.textLabel setText:@"桌子"];
                    cell.imageView.image = [UIImage imageNamed:@"diningroom_desk.png"];
                    [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                    break;
                case 2:
                    [cell.textLabel setText:@"茶几"];
                    cell.imageView.image = [UIImage imageNamed:@"diningroom_gradevin.png"];
                    [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                    break;
                case 3:
                    [cell.textLabel setText:@"沙发"];
                    cell.imageView.image = [UIImage imageNamed:@"parlour.png"];
                    [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                    break;
                default:
                    break;
            }
        }
            
            break;
        case DrawerSectionRecentScan:{
            switch (indexPath.row) {
                case 0:
                    [cell.textLabel setText:@"衣柜"];
                    cell.imageView.image = [UIImage imageNamed:@"diningroom.png"];
                    [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                    break;
                case 1:
                    [cell.textLabel setText:@"床头柜"];
                    cell.imageView.image = [UIImage imageNamed:@"studyroom.png"];
                    [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                    break;
                case 2:
                    [cell.textLabel setText:@"大桌子"];
                    cell.imageView.image = [UIImage imageNamed:@"bedroom.png"];
                    [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
                    break;
                case 3:
                    [cell.textLabel setText:@"花盆"];
                    cell.imageView.image = [UIImage imageNamed:@"childrenroom.png"];
                    [cell setAccessoryType:UITableViewCellAccessoryCheckmark];
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
            return @"模型";
        case DrawerSectionRecentScan:
            return @"最近浏览";
        default:
            return nil;
    }
}


@end
