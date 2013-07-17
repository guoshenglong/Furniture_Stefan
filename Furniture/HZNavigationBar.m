//
//  HZNavigationBar.m
//  top100
//
//  Created by Dai Cloud on 12-7-13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "HZNavigationBar.h"
#import <QuartzCore/QuartzCore.h>

@interface HZNavigationBar ()

-(void) applyDefaultStyle;

@end

@implementation HZNavigationBar

- (void)drawRect:(CGRect)rect {
    UIImage *image;
    /*if([[dataEngine GetInstance] gethome])
     image= [UIImage imageNamed: @"topx.png"];
     else 
     */
    image= [UIImage imageNamed: @"topbg.png"];
    [image drawInRect:rect];
}


-(void)willMoveToWindow:(UIWindow *)newWindow{
    [super willMoveToWindow:newWindow];
    [self applyDefaultStyle];
}

- (void)applyDefaultStyle {
    // add the drop shadow
    self.layer.shadowColor = [[UIColor blackColor] CGColor];
    self.layer.shadowOffset = CGSizeMake(0.0, 1.2);
    self.layer.shadowRadius = 1.5;
    self.layer.shadowOpacity = 0.25;
    self.layer.masksToBounds = NO;
    self.layer.shouldRasterize = YES;
}
@end
