//
//  MessageView.h
//
//  Created by 国翔 韩 on 12-11-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface MessageView : UILabel

-(id)initWithText:(NSString *)text;

-(void)hideView:(NSNumber *)flag;
@end
