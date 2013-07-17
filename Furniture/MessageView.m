//
//  MessageView.m
//
//  Created by 国翔 韩 on 12-11-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#define kMessageFont 16
#define kGapWidth 15
#define kGapHeight 20


#import "MessageView.h"
#import "AppDelegate.h"

@implementation MessageView

- (id)initWithText:(NSString *)text
{
    self = [super init];
    if (self) {
        CGSize contrainSize=CGSizeMake(280, 400);
        
        CGSize trueSize=[text sizeWithFont:[UIFont boldSystemFontOfSize:kMessageFont] constrainedToSize:contrainSize lineBreakMode:UILineBreakModeWordWrap];
        //y==(contrainSize.height-(trueSize.height+2*kGapHeight))/2
        AppDelegate *appDeelgate=(AppDelegate *)[[UIApplication sharedApplication]delegate];
        [self setFrame:CGRectMake((appDeelgate.window.frame.size.width-(trueSize.width+2*kGapWidth))/2, appDeelgate.window.frame.size.height/2-50, trueSize.width+2*kGapWidth, trueSize.height+2*kGapHeight)];
        self.layer.masksToBounds = YES;
        self.layer.cornerRadius = 6;
        [self setTextAlignment:UITextAlignmentCenter];
        [self setBackgroundColor:[UIColor blackColor]];
        [self setAlpha:0.8];
        [self setFont:[UIFont boldSystemFontOfSize:kMessageFont]];
        [self setTextColor:[UIColor whiteColor]];
        [self setNumberOfLines:0];
        [self setText:text];
    }
    return self;
}

-(BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event
{
    return NO;
}

-(void)hideView:(NSNumber *)flag
{
    if([flag boolValue])
    {
        [UIView beginAnimations:nil context:nil];
    }
    [self setAlpha:0.0];
    if([flag boolValue])
    {
        [UIView commitAnimations];
    }
    [self performSelector:@selector(removeFromSuperview) withObject:nil afterDelay:0.3];
}
@end
