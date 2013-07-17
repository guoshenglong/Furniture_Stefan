//
//  SideDrawerViewController.h
//  Furniture0701
//
//  Created by 郭胜龙 on 13-7-15.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, DrawerSection)
{
    DrawerSectionViewModels,
    DrawerSectionRecentScan
};

@interface SideDrawerViewController : UIViewController<UITableViewDataSource,UITableViewDelegate>
@property (nonatomic,strong)UITableView * tableView;
@end
