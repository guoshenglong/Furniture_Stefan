//
//  FolderCoverView.m
//  top100
//
//  Created by Dai Cloud on 12-7-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "FolderCoverView.h"
#import <QuartzCore/QuartzCore.h>


@implementation FolderCoverView

@synthesize position = _position;
@synthesize highlight = _highlight;
@synthesize cover=_cover;

- (id)initWithFrame:(CGRect)frame offset:(CGFloat)delta
{
    self = [super initWithFrame:frame];
    if (!self) return nil;
    
    [self createHighlightWithFrame:frame];
    
    self.cover = [[UIView alloc] initWithFrame:CGRectMake(0, 0, frame.size.width, frame.size.height-delta)];
    self.cover.backgroundColor = [UIColor whiteColor];
    self.cover.alpha = 0.0;
    
    [self addSubview:self.cover];
    
    return self;
}

- (void)createHighlightWithFrame:(CGRect)aFrame {
    CGRect frame = aFrame;
    frame.size.height = 1.f;
    
    self.highlight = [CALayer layer];
    self.highlight.frame = frame;
    self.highlight.anchorPoint = CGPointZero;
    self.highlight.backgroundColor = [UIColor colorWithWhite:1.f alpha:0.3f].CGColor;
    [self.layer addSublayer:self.highlight];
}

- (void)setIsTopView:(BOOL)isTop {
    self.highlight.position = CGPointMake(0, isTop ? (self.frame.size.height-1) : 0);
}


@end
