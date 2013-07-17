//
//  CommonHelper.m
//  ManHuaZhuo
//
//  Created by 国翔 韩 on 12-10-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CommonHelper.h"
#import "sys/utsname.h"
#import "MessageView.h"

@interface ModalAlertDelegate : NSObject <UIAlertViewDelegate>
{
	CFRunLoopRef currentLoop;
	NSUInteger index;
}
@property (readonly) NSUInteger index;
@end

@implementation ModalAlertDelegate
@synthesize index;

// Initialize with the supplied run loop
-(id) initWithRunLoop: (CFRunLoopRef)runLoop 
{
	if (self = [super init]) currentLoop = runLoop;
	return self;
}

// User pressed button. Retrieve results
-(void) alertView: (UIAlertView*)aView clickedButtonAtIndex: (NSInteger)anIndex 
{
	index = anIndex;
	CFRunLoopStop(currentLoop);
}

@end


BOOL _isClickAlert;//是否点击了选择对话框
int _clickIndex;//0-立即升级，1-下次再说

static CommonHelper *instance;

@implementation CommonHelper

+(CommonHelper *)sharedInstance
{
    if(instance==nil)
    {
        instance=[[CommonHelper alloc] init];
    }
    return instance;
}

-(void)dealloc
{
    
    instance=nil;
    
}

-(BOOL)showAlertWithResult:(NSString *)msg
{
    UIAlertView *alert=[[UIAlertView alloc] initWithTitle:@"温馨提示" message:msg delegate:self cancelButtonTitle:@"立即升级" otherButtonTitles:@"下次再说",nil];
    [alert performSelectorOnMainThread:@selector(show) withObject:nil waitUntilDone:YES];
    while (!_isClickAlert) {
        [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
    }    
    
    BOOL resultFlag=NO;
    if(_clickIndex==0)
    {
        resultFlag= YES;
    }
    
    return resultFlag;
}



#pragma mark - alert delegate
-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    _clickIndex=buttonIndex;
    _isClickAlert=YES;
}

+(void)showCustomHud:(UIImage *)image title:(NSString *)title targetView:(UIView *)targetView
{
    MBProgressHUD *hud=[[MBProgressHUD alloc] initWithView:targetView];
    [targetView addSubview:hud];
    UIImageView *imgView=[[UIImageView alloc] initWithImage:image];
    hud.customView=imgView;
    
    imgView=nil;
    hud.mode=MBProgressHUDModeCustomView;
    [hud setLabelText:title];
    [hud show:YES];
    [hud hide:YES afterDelay:1.5];
}


+(MBProgressHUD *) showHud:(id<MBProgressHUDDelegate>) delegate title:(NSString *) title  selector:(SEL) selector arg:(id) arg  targetView:(UIView *)targetView
{
    MBProgressHUD *hud = [[MBProgressHUD alloc] initWithView:targetView];
    [targetView addSubview:hud];
    hud.removeFromSuperViewOnHide = YES;
    hud.delegate = delegate;
    hud.labelText = title;
    [hud showWhileExecuting:selector 
                   onTarget:delegate 
                 withObject:arg 
                   animated:YES];
    return hud;
}

+(BOOL) connectedToNetwork
{
    // Create zero addy
    struct sockaddr_in zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin_len = sizeof(zeroAddress);
    zeroAddress.sin_family = AF_INET;
    
    // Recover reachability flags
    SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);    
    SCNetworkReachabilityFlags flags;
    
    BOOL didRetrieveFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
    CFRelease(defaultRouteReachability);
    
    if (!didRetrieveFlags) 
    {
        printf("Error. Could not recover network reachability flags\n");
        return NO;
    }
    
    BOOL isReachable = ((flags & kSCNetworkFlagsReachable) != 0);
    BOOL needsConnection = ((flags & kSCNetworkFlagsConnectionRequired) != 0);
    return (isReachable && !needsConnection) ? YES : NO;
}

+(void)showAlert:(NSString *)title msg:(NSString *)msg
{
    if(title==nil)
    {
        title=@"温馨提示";
    }
    UIAlertView *alert=[[UIAlertView alloc] initWithTitle:title message:msg delegate:nil cancelButtonTitle:@"好" otherButtonTitles: nil];
    [alert show];
   
}

+(ClientType)getClientTypeID
{
    ClientType type=0;
    struct utsname systemInfo;  
    uname(&systemInfo);  
    NSString *device=[NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    if( [device isEqualToString:@"i386"] || [device isEqualToString:@"x86_64"] ) type=14;
    else if( [device isEqualToString:@"iPhone1,1"] ) type=ClientiPhone1G;
    else if( [device isEqualToString:@"iPhone1,2"] ) type=ClientiPhone2G;
    else if( [device isEqualToString:@"iPhone2,1"] ) type=ClientiPhone3GS;
    else if( [device isEqualToString:@"iPhone3,1"] ) type=ClientiPhone4;
    else if( [device isEqualToString:@"iPod1,1"] ) type=ClientiPod1G;
    else if( [device isEqualToString:@"iPod2,1"] ) type=ClientiPod2G;
    else if( [device isEqualToString:@"iPod3,1"] ) type=ClientiPod3G;
    else if( [device isEqualToString:@"iPod4,1"] ) type=ClientiPod4G;
    else if( [device isEqualToString:@"iPad1,1"] ) type=ClientiPad1;
    else if( [device isEqualToString:@"iPad2,1"] ) type=ClientiPad2;
    else if( [device isEqualToString:@"iPad3,1"] ) type=ClientiPad3;
    else if( [device isEqualToString:@"iPhone4,1"]) type=ClientiPhone4S;
    else if( [device isEqualToString:@"iPhone5,1"]) type=ClientiPhone5;
    return type;
}


+(void)showMessage:(NSString *)message inView:(UIView *)view
{
    MessageView *msgView=[[MessageView alloc] initWithText:message];
    [msgView setAlpha:0];
    [view addSubview:msgView];
    [UIView beginAnimations:nil context:nil];
    [msgView setAlpha:0.8];
    [UIView commitAnimations];
    
    
    [msgView performSelector:@selector(hideView:) withObject:[NSNumber numberWithBool:YES] afterDelay:5];
}


+(BOOL)showMsg:(NSString *)msg
{
    CFRunLoopRef currentLoopRef=CFRunLoopGetCurrent();
    
    // Create Alert
	ModalAlertDelegate *madelegate = [[ModalAlertDelegate alloc] initWithRunLoop:currentLoopRef];
    UIAlertView *alert=[[UIAlertView alloc] initWithTitle:@"温馨提示" message:msg delegate:madelegate cancelButtonTitle:@"是" otherButtonTitles:@"否", nil];
    [alert show];
    
    CFRunLoopRun();
    
    int index=madelegate.index;
   
    if(index==0)
    {
        return YES;
    }
    else {
       return NO;
    }
}

@end
