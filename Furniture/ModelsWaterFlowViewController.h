//
//  ModelsWaterFlowViewController.h
//  Furniture0701
//
//  Created by li yajin on 13-7-14.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UIFolderTableView.h"
#import "WaterFlowView.h"
#import "ImageViewCell.h"
#import "BaseViewController.h"

@interface ModelsWaterFlowViewController : BaseViewController<UITableViewDataSource, UITableViewDelegate,UIScrollViewDelegate,WaterFlowViewDelegate,WaterFlowViewDataSource>

{
    BOOL isLoadingNext;
    int _pageIndex;
    NSMutableArray *modelList;
}

@property(nonatomic,retain)WaterFlowView *waterView;

-(void)startModelListInThread;//线程中请求推荐模型

@end
