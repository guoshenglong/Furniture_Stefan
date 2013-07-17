//
//  SubCateViewController.m
//  top100
//
//  Created by Dai Cloud on 12-7-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "SubCateViewController.h"
#define COLUMN 4

@interface SubCateViewController ()

@end

@implementation SubCateViewController

@synthesize subCates=_subCates;
@synthesize cateVC=_cateVC;

- (void)dealloc
{
    _subCates = nil;
    _cateVC = nil;

}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    self.view.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"tmall_bg_furley.png"]];
    
    // init cates show
    int total = self.subCates.count;
#define ROWHEIHT 70    
    int rows = (total / COLUMN) + ((total % COLUMN) > 0 ? 1 : 0);
    
    for (int i=0; i<total; i++) {
        int row = i / COLUMN;
        int column = i % COLUMN;
        NSDictionary *data = [self.subCates objectAtIndex:i];
        
        UIView *view = [[UIView alloc] initWithFrame:CGRectMake(80*column, ROWHEIHT*row, 80, ROWHEIHT)];
        view.backgroundColor = [UIColor clearColor];
        UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
        btn.frame = CGRectMake(15, 15, 50, 50);
        btn.tag = i;
        [btn addTarget:self.cateVC 
                action:@selector(subCateBtnAction:) 
      forControlEvents:UIControlEventTouchUpInside];

        [btn setBackgroundImage:[UIImage imageNamed:[[data objectForKey:@"imageName"] stringByAppendingFormat:@".png"]] 
                           forState:UIControlStateNormal];
        
        [view addSubview:btn];
        
        UILabel *lbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 65, 80, 14)];
        lbl.textAlignment =
        NSTextAlignmentCenter;
        lbl.textColor = [UIColor colorWithRed:204/255.0 
                                        green:204/255.0 
                                         blue:204/255.0 
                                        alpha:1.0];
        lbl.font = [UIFont systemFontOfSize:12.0f];
        lbl.backgroundColor = [UIColor clearColor];
        lbl.text = [data objectForKey:@"name"];
        [view addSubview:lbl];
        
        [self.view addSubview:view];
    }
    
    CGRect viewFrame = self.view.frame;
    viewFrame.size.height = ROWHEIHT * rows + 19;
    self.view.frame = viewFrame;
    
}

@end
