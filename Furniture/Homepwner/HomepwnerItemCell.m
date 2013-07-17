//
//  HomepwnerItemCell.m
//  Homepwner
//
//  Created by huzhengnan on 13-7-9.
//  Copyright (c) 2013年 huzhengnan. All rights reserved.
//

#import "HomepwnerItemCell.h"

@implementation HomepwnerItemCell

- (IBAction)changeImage:(id)sender
{
    NSLog(@"Someone clicked this button!");
    // UIImage *baseImage = [UIImage imageNamed:@"灰色喜爱.PNG"];
    UIButton *btn = (UIButton *)sender;
    btn.selected = !btn.selected;
    // NSLog(@"%@", btn);
}

@end
