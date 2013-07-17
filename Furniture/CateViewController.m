//
//  CateViewController.m
//  top100
//
//  Created by Dai Cloud on 12-7-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CateViewController.h"
#import "SubCateViewController.h"
#import "CateTableCell.h"
#import "UIFolderTableView.h"


@interface CateViewController () <UIFolderTableViewDelegate>

@property (strong, nonatomic) SubCateViewController *subVc;
@property (strong, nonatomic) NSDictionary *currentCate;


@end

@implementation CateViewController

@synthesize cates=_cates;
@synthesize subVc=_subVc;
@synthesize currentCate=_currentCate;
@synthesize tableView=_tableView;
//@synthesize waterView;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        NSLog(@"nav:%@", self.navigationController);
        NSLog(@"CateViewController ------ huzhengnan光荣地出现在CateViewController");
        /*
        NSInteger newheight = 0;
        //改变view的大小
        UIView *oldView = [[self navigationController]view];
        //UIView *oldView = self.view;
        NSLog(@"oldView = %@",oldView);
        CGRect oldRect = oldView.bounds;
        NSLog(@"oldddddd height = %f",oldRect.size.height);
        
        if (oldRect.size.height > 410.0) {
            
            NSLog(@"size height > 20!!!!!!!!!!!!!!!!!!!!");
            newheight = oldRect.size.height - 49;
            CGRect newRect = CGRectMake(oldRect.origin.x, oldRect.origin.y+24.5, oldRect.size.width, newheight);
            [oldView setBounds:newRect];
        }else{
            newheight = oldRect.size.height;
            CGRect newRect = CGRectMake(oldRect.origin.x, oldRect.origin.y, oldRect.size.width, newheight);
            [oldView setBounds:newRect];
        }
         
        
        NSLog(@"new height = %d",newheight);**/
        
        UIImage *baseImage = [UIImage imageNamed:@"navigator.png"];
        // UIImage *backgroundImage = [self scaleImage:baseImage toScale:1];
        [self.navigationController.navigationBar setBackgroundImage:baseImage forBarMetrics:UIBarMetricsDefault];
    }
         
    return self;
}


- (void)dealloc
{
    _cates = nil;
    _subVc = nil;
    _currentCate = nil;
    _tableView = nil;
}

-(NSArray *)cates
{
    if (_cates == nil){
        
        NSURL *url = [[NSBundle mainBundle] URLForResource:@"Category" withExtension:@"plist"];
        _cates = [NSArray arrayWithContentsOfURL:url];
        
    }
    
    return _cates;
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    [UIFolderTableView class];
    [[self tabBarController] setHidesBottomBarWhenPushed:YES];
    
    // 设置导航栏的一些内容
    UILabel *title = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 100, 44)];
    [title setText:@"家具选择"];
    [title setTextAlignment:NSTextAlignmentCenter];
    [title setFont:[UIFont boldSystemFontOfSize:20]];
    [title setTextColor:[UIColor colorWithRed:(140.0/255.0) green:(116.0/255.0) blue:(50.0/255.0) alpha:1]];
    [title setBackgroundColor:[UIColor clearColor]];
    [[self navigationItem] setTitleView:title];
    
    // self.navigationItem.
    NSLog(@"家具选择%@", [self navigationController]);
    UIImage *baseImage = [UIImage imageNamed:@"navigator.png"];
    // UIImage *backgroundImage = [self scaleImage:baseImage toScale:1];
    [self.navigationController.navigationBar setBackgroundImage:baseImage forBarMetrics:UIBarMetricsDefault];
}

- (void)viewWillAppear:(BOOL)animated
{
    NSLog(@"viewWillAppear");
    [super viewWillAppear:animated];
    
    /*
    NSInteger newheight = 0;
    //改变view的大小
    UIView *oldView = [[self navigationController]view];
    //UIView *oldView = self.view;
    NSLog(@"oldView = %@",oldView);
    CGRect oldRect = oldView.bounds;
    NSLog(@"old height = %f",oldRect.size.height);
    
    if (oldRect.size.height > 400.0) {
        NSLog(@"size height > 20!!!!!!!!!!!!!!!!!!!!");
        newheight = oldRect.size.height - 49;
        CGRect newRect = CGRectMake(oldRect.origin.x, oldRect.origin.y+24.5, oldRect.size.width, newheight);
        [oldView setBounds:newRect];
    }
    
    NSLog(@"new height = %d",newheight);
    */
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(void)backAction
{
    [self.navigationController popViewControllerAnimated:YES];
}


#pragma mark - Table view data source

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    NSLog(@"count = %d",self.cates.count);

    return self.cates.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"cate_cell";

    CateTableCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil) {
        cell = [[CateTableCell alloc] initWithStyle:UITableViewCellStyleSubtitle
                                      reuseIdentifier:CellIdentifier];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
 
    }
    
    NSDictionary *cate = [self.cates objectAtIndex:indexPath.row];
    cell.logo.image = [UIImage imageNamed:[[cate objectForKey:@"imageName"] stringByAppendingString:@".png"]];
    cell.title.text = [cate objectForKey:@"name"];
    //NSLog(@"title = %@ \n",cell.title.text);
    
    NSMutableArray *subTitles = [[NSMutableArray alloc] init];
    NSArray *subClass = [cate objectForKey:@"subClass"];
    for (int i=0; i < MIN(4,  subClass.count); i++) {
        [subTitles addObject:[[subClass objectAtIndex:i] objectForKey:@"name"]];
        //NSLog(@"subtitle = %@ \n",[[subClass objectAtIndex:i] objectForKey:@"name"]);
    }
    cell.subTtile.text = [subTitles componentsJoinedByString:@"/"];
    subTitles = nil;
    
    return cell;
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSLog(@"select a row");
    SubCateViewController *subVc = [[SubCateViewController alloc]
                  initWithNibName:NSStringFromClass([SubCateViewController class]) 
                  bundle:nil];
  
    NSDictionary *cate = [self.cates objectAtIndex:indexPath.row];
    NSLog(@"selected row = %d\n",indexPath.row);
    
    subVc.subCates = [cate objectForKey:@"subClass"];
    self.currentCate = cate;
    subVc.cateVC = self;
    
    self.tableView.scrollEnabled = NO;
    UIFolderTableView *folderTableView = (UIFolderTableView *)tableView;
    [folderTableView openFolderAtIndexPath:indexPath WithContentView:subVc.view 
                                 openBlock:^(UIView *subClassView, CFTimeInterval duration, CAMediaTimingFunction *timingFunction){
                                     // opening actions
                                 } 
                                closeBlock:^(UIView *subClassView, CFTimeInterval duration, CAMediaTimingFunction *timingFunction){
                                    // closing actions
                                } 
                           completionBlock:^{
                               // completed actions
                               self.tableView.scrollEnabled = YES;
                           }];
    
}

-(CGFloat)tableView:(UIFolderTableView *)tableView xForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 40;
}

-(void)subCateBtnAction:(UIButton *)btn
{
    
    /*
    NSDictionary *subCate = [[self.currentCate objectForKey:@"subClass"] objectAtIndex:btn.tag];
    NSString *name = [subCate objectForKey:@"name"];
    UIAlertView *Notpermitted=[[UIAlertView alloc] initWithTitle:@"子类信息"
                                                         message:[NSString stringWithFormat:@"名称:%@, ID: %@", name, [subCate objectForKey:@"classID"]]
                                                        delegate:nil
                                               cancelButtonTitle:@"确认"
                                               otherButtonTitles:nil];
     [Notpermitted show];
    Notpermitted = nil;
     
    //瀑布流控件
    waterView=[[WaterFlowView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height-44-44)];
    [waterView setTag:600];
    [waterView setWaterFlowViewDelegate:self];
    [waterView setWaterFlowViewDatasource:self];
    
    
    _pageIndex=0;
    [NSThread detachNewThreadSelector:@selector(startModelListInThread) toTarget:self withObject:nil];
    */
    
    ModelsWaterFlowViewController *modelsFlowController = [[ModelsWaterFlowViewController alloc] init];
    [[self navigationController] pushViewController:modelsFlowController animated:YES];

}




@end
