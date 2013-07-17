//
//  UIView+screenshot.h
//  top100
//
//  Created by Dai Cloud on 12-7-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIView (screenshot)

- (UIImage *)screenshotWithOffset:(CGFloat)deltaY;
- (UIImage *)screenshot;

@end
