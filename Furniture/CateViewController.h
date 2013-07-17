//
//  CateViewController.h
//  top100
//
//  Created by Dai Cloud on 12-7-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UIFolderTableView.h"
#import "WaterFlowView.h"
#import "ImageViewCell.h"
#import "BaseViewController.h"
#import "ModelsWaterFlowViewController.h"

@interface CateViewController : BaseViewController <UITableViewDataSource, UITableViewDelegate,UIScrollViewDelegate,WaterFlowViewDelegate,WaterFlowViewDataSource>
/*
{
    BOOL isLoadingNext;
    int _pageIndex;
    NSMutableArray *modelList;
}
*/

@property (strong, nonatomic) NSArray *cates;
@property (strong, nonatomic) IBOutlet UIFolderTableView *tableView;
//@property(nonatomic,retain)WaterFlowView *waterView;

//-(void)startModelListInThread;//线程中请求推荐模型


@end
