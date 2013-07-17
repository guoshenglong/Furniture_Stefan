//
//  WaitView.m
//  -巴士商店-
//
//  Created by TGBUS on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "WaitView.h"
#import <QuartzCore/QuartzCore.h>

@implementation WaitView

@synthesize delegate;
@synthesize url;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        [self setBackgroundColor:[UIColor colorWithRed:225/255.0 green:225/255.0 blue:225/255.0 alpha:1.0f]];
        
        lblName=[[UILabel alloc] init];
        [lblName setTag:800];
        [lblName.layer setShadowColor:[UIColor blackColor].CGColor];
        [lblName.layer setShadowOpacity:0.5];
        [lblName setNumberOfLines:0];
        [lblName.layer setShadowOffset:CGSizeMake(5, 3)];
        [lblName setFrame:CGRectMake(0, self.frame.size.height/2-80, frame.size.width, 80)];
        [lblName setTextAlignment:UITextAlignmentCenter];
        [lblName setBackgroundColor:[UIColor clearColor]];
        [lblName setFont:[UIFont boldSystemFontOfSize:30]];
        [lblName setTextColor:[UIColor grayColor]];
        [lblName setText:@"漫画桌"];
        [self addSubview:lblName];
        
        lblSite=[[UILabel alloc] init];
        [lblSite.layer setShadowColor:[UIColor blackColor].CGColor];
        [lblSite.layer setShadowOpacity:0.5];
        [lblSite setNumberOfLines:0];
        [lblSite.layer setShadowOffset:CGSizeMake(5, 3)];
        [lblSite setFrame:CGRectMake(0, self.frame.size.height/2-30, frame.size.width, 40)];
        [lblSite setTextAlignment:UITextAlignmentCenter];
        [lblSite setBackgroundColor:[UIColor clearColor]];
        [lblSite setFont:[UIFont boldSystemFontOfSize:20]];
//        [lblSite setTextColor:[UIColor colorWithRed:194/255.0 green:194/255.0 blue:194/255.0 alpha:1.0f]];
        [lblSite setTextColor:[UIColor grayColor]];
//        [lblSite setText:@"www.manhuazhuo.com"];
        [self addSubview:lblSite];
        
        actView=[[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
        [actView setTag:900];
        [actView setBackgroundColor:[UIColor clearColor]];
        [actView setCenter:self.center];
        [actView setFrame:CGRectMake(actView.frame.origin.x, lblName.frame.origin.y+90, 20, 20)];
        [actView startAnimating];
        [self addSubview:actView];
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

-(void)setFrame:(CGRect)frame
{
    [super setFrame:frame];
    [lblName setFrame:CGRectMake(0, self.frame.size.height/2-80, frame.size.width, lblName.frame.size.height)];
    [lblSite setFrame:CGRectMake(0, self.frame.size.height/2-30, frame.size.width, lblSite.frame.size.height)];
    [actView setCenter:self.center];
    [actView setFrame:CGRectMake(actView.frame.origin.x, lblName.frame.origin.y+80, 20, 20)];
}

-(void)setTitleText:(NSString *)text url:(NSString *)_url
{
    [self setTitleText:text];
    self.url=_url;
}

-(void)setTitleText:(NSString *)text
{
    if(text==nil)
    {
        [lblName setText:NSLocalizedString(@"数据加载失败了\n轻击视图重新加载", @"")];
        [lblSite setText:@""];
    }
    else
    {
        [lblName setText:text];
    }
    [actView stopAnimating];
    isDownloadFailed=YES;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if(isDownloadFailed)
    {
        isDownloadFailed=NO;
        [self reStart];
        if([delegate respondsToSelector:@selector(waitViewTap:)])
        {
            [delegate waitViewTap:url];
        }
    }
}

-(void)dealloc
{

    lblSite=nil;
    self.url=nil;
    self.delegate=nil;

    actView=nil;
 
    lblName=nil;
 
}

-(void)reStart//数据加载失败后，重新加载数据，然后重新显示-巴士商店-，并且启动风火轮
{
    [lblName setText:@"漫画桌"];
//    [lblSite setText:@"www.iphonecake.com"];
    [actView startAnimating];
}


@end
