//
//  CommonHelper.h
//  ManHuaZhuo
//
//  Created by 国翔 韩 on 12-10-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MBProgressHUD.h"
#import <SystemConfiguration/SystemConfiguration.h>
#include <netdb.h>
#import "Constants.h"

@interface CommonHelper : NSObject<NSObject>

+(CommonHelper *)sharedInstance;

-(BOOL)showAlertWithResult:(NSString *)msg;//选择对话框
+(void) showCustomHud:(UIImage *)image title:(NSString *)title targetView:(UIView *)targetView;

//后台执行某个函数，期间出现风火轮，函数执行完毕自动消失
+(MBProgressHUD *) showHud:(id<MBProgressHUDDelegate>) delegate title:(NSString *) title  selector:(SEL) selector arg:(id) arg  targetView:(UIView *)targetView;
+(BOOL) connectedToNetwork;
+(void)showAlert:(NSString *)title msg:(NSString *)msg;
+(ClientType)getClientTypeID;
+(BOOL)showMsg:(NSString *)msg;
+(void)showMessage:(NSString *)message inView:(UIView *)view;

@end
