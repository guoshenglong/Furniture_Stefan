//
//  WaitView.h
//  -巴士商店-
//
//  Created by TGBUS on 12-6-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

@protocol WaitViewDelegate <NSObject>

-(void)waitViewTap:(NSString *)url;//轻击后返回url，用于重新加载数据
//-(void)waitViewTap:(NSString *)url tag:(NSNumber *)tag;
@end
#import <UIKit/UIKit.h>

@interface WaitView : UIView
{
    UILabel *lblName;
    UILabel *lblSite;
    UIActivityIndicatorView *actView;
    
    BOOL isDownloadFailed;//是否加载数据失败了，默认是NO
}

@property(nonatomic,assign)id<WaitViewDelegate>delegate;
@property(nonatomic,retain)NSString *url;//正在请求的url

-(void)setTitleText:(NSString *)text url:(NSString *)_url;
-(void)setTitleText:(NSString *)text;
-(void)reStart;
@end
