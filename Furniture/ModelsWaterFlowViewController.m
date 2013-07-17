//
//  ModelsWaterFlowViewController.m
//  Furniture0701
//
//  Created by li yajin on 13-7-14.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import "ModelsWaterFlowViewController.h"

@implementation ModelsWaterFlowViewController

@synthesize waterView;

- (void)loadView
{
    NSLog(@"!!!!!!!!!!!!!!!!LOADVIEW!!!!!!!!!!!!!!!!!!!");
    [super loadView];
    
    /*
    //搜索按钮
    UIButton *btn=[UIButton buttonWithType:UIButtonTypeCustom];
    [btn setFrame:CGRectMake(0, 7, 48, 30)];
    [btn setBackgroundImage:[UIImage imageNamed:@"nav_search.png"] forState:UIControlStateNormal];
    [btn setBackgroundImage:[UIImage imageNamed:@"nav_search_pressed.png"] forState:UIControlStateHighlighted];
    [btn addTarget:self action:@selector(searchAction) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.rightBarButtonItem=[[UIBarButtonItem alloc] initWithCustomView:btn];
     */
    
    //瀑布流控件
    waterView=[[WaterFlowView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height-44-44)];
    [waterView setTag:600];
    [waterView setWaterFlowViewDelegate:self];
    [waterView setWaterFlowViewDatasource:self];
    [self.view addSubview:waterView];
    
}

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    [self showLoadingView];
    
    
    _pageIndex=0;
    [NSThread detachNewThreadSelector:@selector(startModelListInThread) toTarget:self withObject:nil];
}

#pragma mark WaterFlowViewDataSource
- (NSInteger)numberOfColumsInWaterFlowView:(WaterFlowView *)waterFlowView{
    return 2;
    /*
    //NSLog(@"-----numberOfColumsInWaterFlowView!-----");
    if([[UIDevice currentDevice] userInterfaceIdiom]==UIUserInterfaceIdiomPhone)
    {
        return 3;
    }
    else {
        return 6;
    }
     */
}

- (NSInteger)numberOfAllWaterFlowView:(WaterFlowView *)waterFlowView{
    //NSLog(@"-----numberOfAllWaterFlowView!-----");
    
    return [modelList count];
}

- (UIView *)waterFlowView:(WaterFlowView *)waterFlowView cellForRowAtIndexPath:(IndexPath *)indexPath{
    
    //NSLog(@"-----cellForRowAtIndexPath111111-----");
    ImageViewCell *view = [[ImageViewCell alloc] initWithIdentifier:nil];
    //NSLog(@"-----cellForRowAtIndexPath222222-----");
    return view;
}


-(void)waterFlowView:(WaterFlowView *)waterFlowView  relayoutCellSubview:(UIView *)view withIndexPath:(IndexPath *)indexPath{
    
    //NSLog(@"-----relayoutCellSubview!-----");
    
    //arrIndex是某个数据在总数组中的索引
    int arrIndex = indexPath.row * waterFlowView.columnCount + indexPath.column;
    
    NSString *s =[modelList objectAtIndex:arrIndex];
    
    
    ImageViewCell *imageViewCell = (ImageViewCell *)view;
    imageViewCell.indexPath = indexPath;
    imageViewCell.columnCount = waterFlowView.columnCount;
    [imageViewCell relayoutViews];
    
    //[(ImageViewCell *)view setImageWithURL:[NSURL URLWithString:book.bookIconURL]];
    [(ImageViewCell *)view setImage:[UIImage imageNamed:s]];
    
}


#pragma mark WaterFlowViewDelegate
- (CGFloat)waterFlowView:(WaterFlowView *)waterFlowView heightForRowAtIndexPath:(IndexPath *)indexPath{
    //NSLog(@"-----heightForRowAtIndexPath!-----");
    return 140;
    
}

- (void)waterFlowView:(WaterFlowView *)waterFlowView didSelectRowAtIndexPath:(IndexPath *)indexPath{
    
    /*
     //    NSLog(@"indexpath row == %d,column == %d",indexPath.row,indexPath.column
     int clickIndex=indexPath.row*3+indexPath.column;
     BookModel *book=[booklist objectAtIndex:clickIndex];
     NSLog(@"%@",book);
     BookDetailViewController *detailVController=[[BookDetailViewController alloc] initWithBook:book];
     [self.navigationController pushViewController:detailVController animated:YES];
     [detailVController release];
     */
    NSLog(@"-----------------selected------------------");
}

-(void)waterFlowView:(WaterFlowView *)waterFlowViewNeedReqeustData
{
    NSLog(@"-----waterFlowViewNeedRequestData!-----");
    if(!isLoadingNext)
    {
        isLoadingNext=YES;
        _pageIndex++;
        [NSThread detachNewThreadSelector:@selector(startModelListInThread) toTarget:self withObject:nil];
    }
}

#pragma mark - private method
-(void)startModelListInThread
{
    
    NSLog(@"-----startModelListInThread!-----");
    
    //NSAutoreleasePool *pool=[[NSAutoreleasePool alloc] init];
    
    //ResponseModel *response=[BookNet startRecommandlistByPage:_pageIndex pageSize:40];
    if(_pageIndex==0)
    {
        //self.booklist=response.resultInfo;
        modelList = [NSMutableArray arrayWithObjects:@"bedroom.png",@"bedroom.png",@"bedroom.png",@"bedroom.png",@"bedroom.png",@"bedroom.png",@"bedroom.png",@"bedroom.png",@"bedroom.png",@"bedroom.png", nil];
    }
    else {
        //[self.modelList addObjectsFromArray:response.resultInfo];
        [modelList addObject:@"bedroom.png"];
        [modelList addObject:@"bedroom.png"];
        [modelList addObject:@"bedroom.png"];
    }
    isLoadingNext=NO;
    
    dispatch_async(dispatch_get_main_queue(), ^(void){
        //if(response.error!=nil)
        //{
        //    [self showErrorView];
        //    return;
        //}
        [waterView reloadData];
        [self hideLoadingView];
    });
    //[pool release];
    
}


@end
