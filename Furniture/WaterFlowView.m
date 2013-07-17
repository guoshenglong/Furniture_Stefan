//
//  WaterFlowView.m
//  WaterFlowViewDemo
//
//  Created by Smallsmall on 12-6-11.
//  Copyright (c) 2012年 activation group. All rights reserved.
//

#import "WaterFlowView.h"

#define TABLEVIEWTAG 1000
#define CELLSUBVIEWTAG 10000

@implementation WaterFlowView
@synthesize columnCount = _columnCount, cellsTotal = _cellsTotal,cellWidth = _cellWidth;
@synthesize waterFlowViewDelegate = _waterFlowViewDelegate,waterFlowViewDatasource = _waterFlowViewDatasource;


-(void)dealloc{

    self.waterFlowViewDelegate = nil;
    self.waterFlowViewDatasource = nil;
    //if([tableviews respondsToSelector:@selector(release)])
    //{
    //    [tableviews release];
    //}
    //[super dealloc];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        //UIActivityIndicatorView实例提供轻型视图，这些视图显示一个标准的旋转进度轮
        //进度轮显示类型，白色背景下显示灰色 
        activityViewLoad = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
        activityViewLoad.frame = CGRectMake(CGRectGetWidth(self.frame)/2, CGRectGetHeight(self.frame)/2, 20, 20);
        activityViewLoad.center = CGPointMake(CGRectGetWidth(self.frame)/2, CGRectGetHeight(self.frame)/2);
        [self addSubview:activityViewLoad];
        //[activityViewLoad release];
        [activityViewLoad startAnimating];
        
        self.contentSize = CGSizeMake(CGRectGetWidth(self.frame), CGRectGetHeight(self.frame)+1);
    }
    return self;
}

//重写父类方法
//UIView的setNeedsLayout方法会默认调用layoutSubViews，处理子视图的数据
-(void)layoutSubviews{
    
    [self relayoutDisplaySubviews];
    
    
    for (UITableView *tableview in tableviews) {
        
        [tableview setFrame:CGRectMake(tableview.frame.origin.x, self.contentOffset.y, CGRectGetWidth(tableview.frame), CGRectGetHeight(tableview.frame))];
        [tableview setContentOffset:self.contentOffset animated:NO];
    }
    
    [super layoutSubviews];
}


-(void)relayoutDisplaySubviews{

    self.columnCount = [self.waterFlowViewDatasource numberOfColumsInWaterFlowView:self];  
    self.cellsTotal = [self.waterFlowViewDatasource numberOfAllWaterFlowView:self];
    
    if (_cellsTotal == 0 || _columnCount == 0) {
        
        return;
    }
    
    self.cellWidth = CGRectGetWidth(self.frame)/_columnCount; //每列的宽度
    
    if (!tableviews) {
        
        tableviews = [[NSMutableArray alloc] initWithCapacity:_columnCount];
        for (int i = 0; i < _columnCount; i++) {
            
            UITableView *tableView = [[UITableView alloc] initWithFrame:CGRectMake(_cellWidth*i, 0, _cellWidth, CGRectGetHeight(self.frame)) style:UITableViewStylePlain];
            tableView.delegate = self;
            tableView.dataSource = self;
            tableView.tag = i + TABLEVIEWTAG; //保存列号
            tableView.showsVerticalScrollIndicator = NO;
            tableView.scrollEnabled = NO;
            tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
            tableView.backgroundColor = [UIColor clearColor];
            [self addSubview:tableView];
//            [tableView release];
            
            [tableviews addObject:tableView];
            //[tableView release];
        }
    }
}

-(void)setWaterFlowViewDatasource:(id<WaterFlowViewDataSource>)waterFlowViewDatasource{

    _waterFlowViewDatasource = waterFlowViewDatasource;
}

-(void)setWaterFlowViewDelegate:(id<WaterFlowViewDelegate>)waterFlowViewDelegate{

    _waterFlowViewDelegate = waterFlowViewDelegate;
  
}

- (void)reloadData{
    
    if (activityViewLoad) {
        
        [activityViewLoad stopAnimating];
        [activityViewLoad removeFromSuperview];
        activityViewLoad = nil;
    }

    [self relayoutDisplaySubviews];
    
    float contenSizeHeight = 0.0f;
    
    for (UITableView *tabelview in tableviews) {
        
         [tabelview reloadData];
        if (contenSizeHeight < tabelview.contentSize.height) {
            
            contenSizeHeight = tabelview.contentSize.height;
        }
    }
    
    contenSizeHeight = contenSizeHeight < CGRectGetHeight(self.frame)?CGRectGetHeight(self.frame)+1:contenSizeHeight;
    self.contentSize = CGSizeMake(self.contentSize.width, contenSizeHeight);
}


- (NSInteger)waterFlowView:(WaterFlowView *)waterFlowView numberOfRowsInColumn:(NSInteger)colunm{
    
    if (waterFlowView.cellsTotal -(colunm + 1) < 0) {
        
        return 0;
    }else{
        return (waterFlowView.cellsTotal -(colunm + 1))/waterFlowView.columnCount+1;
    }
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{

    return [self waterFlowView:self numberOfRowsInColumn:tableView.tag - TABLEVIEWTAG];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
     
    IndexPath *_indextPath = [IndexPath initWithRow:indexPath.row  withColumn:tableView.tag - TABLEVIEWTAG];
    CGFloat cellHeight = [self.waterFlowViewDelegate waterFlowView:self heightForRowAtIndexPath:_indextPath];
    return cellHeight;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    UITableViewCell *cell = nil;
    NSString *cellIndetify = [NSString stringWithFormat:@"cell%d",tableView.tag -TABLEVIEWTAG];
    
    cell = [tableView dequeueReusableCellWithIdentifier:cellIndetify];
    if (cell == nil) {
        
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIndetify];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        
        IndexPath *_indextPath = [IndexPath initWithRow:indexPath.row  withColumn:tableView.tag - TABLEVIEWTAG];
        UIView *cellSub =  [self.waterFlowViewDatasource waterFlowView:self cellForRowAtIndexPath:_indextPath];
        [cell.contentView addSubview:cellSub];
//        [cellSub release];
        cellSub.tag = CELLSUBVIEWTAG;
    }
    
    IndexPath *_indextPath = [IndexPath initWithRow:indexPath.row  withColumn:tableView.tag - TABLEVIEWTAG];
    
    CGFloat cellHeight = [self.waterFlowViewDelegate waterFlowView:self heightForRowAtIndexPath:_indextPath];
    CGRect cellRect = CGRectMake(0, 0, _cellWidth, cellHeight);
    [[cell viewWithTag:CELLSUBVIEWTAG] setFrame:cellRect];
    
    [self.waterFlowViewDatasource waterFlowView:self relayoutCellSubview:[cell viewWithTag:CELLSUBVIEWTAG] withIndexPath:_indextPath];

    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{

    IndexPath *_indextPath = [IndexPath initWithRow:indexPath.row  withColumn:tableView.tag - TABLEVIEWTAG];
    [self.waterFlowViewDelegate waterFlowView:self didSelectRowAtIndexPath:_indextPath];
}

#pragma UIScrollView Delegate
-(void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    if([scrollView isKindOfClass:[UITableView class]])
    {
//        NSLog(@"--%f",scrollView.contentOffset.y);
        CGFloat height=416;
        if([[UIDevice currentDevice] userInterfaceIdiom]==UIUserInterfaceIdiomPad)
        {
            height=1000;
        }
        if(scrollView.contentOffset.y+height>=scrollView.contentSize.height)
        {
            
            [self.waterFlowViewDelegate waterFlowView:self];
            
            if(activityViewLoad)
            {
                [activityViewLoad removeFromSuperview];
                activityViewLoad = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
                activityViewLoad.frame = CGRectMake(CGRectGetWidth(self.frame)/2, scrollView.contentSize.height, 20, 20);
                [self addSubview:activityViewLoad];
                //[activityViewLoad release];
                [activityViewLoad startAnimating];
            }
        }
    }
}

@end
