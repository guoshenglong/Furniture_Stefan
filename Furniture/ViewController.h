//
//  ViewController.h
//  Furniture0701
//
//  Created by 郭胜龙 on 13-7-1.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MetaioSDKViewController.h"
#import "EAGLView.h"
#import <metaioSDK/GestureHandlerIOS.h>

@interface ViewController : MetaioSDKViewController
{
    // pointers to geometries（指向3D模型）
    metaio::IGeometry* m_metaioMan;
    metaio::IGeometry* m_chair;
    metaio::IGeometry* m_tv;
    metaio::IGeometry* m_screen;
    // GestureHandler handles the dragging/pinch/rotation touches
    //手势处理拖拽、缩放、旋转
    GestureHandlerIOS* m_gestureHandler;
    //gesture mask to specify the gestures that are enabled
    //开关变量来标识手势识别enabled
    int m_gestures;
    //indicate if a camera image has been requested from the user
    //表明用户是否做出了拍照的请求
    bool m_imageTaken;
	// remember the TrackingValues
    //记录3D模型实时的方位值
	metaio::TrackingValues m_pose;
}
//geometry button callback to show/hide the geometry and reset the location and scale of the geometry
- (IBAction)onTVButtonClick:(id)sender;
- (IBAction)onChairButtonClick:(id)sender;
- (IBAction)onManButtonClick:(id)sender;

// handle buttom buttons
- (IBAction)onTakePicture:(id)sender;
- (IBAction)onSaveScreen:(id)sender;
- (IBAction)onClearScreen:(id)sender;
@property (unsafe_unretained, nonatomic) IBOutlet UIView *subview;

//show/hide the geometries
- (void)setVisibleTV:(bool)visible;
- (void)setVisibleChair:(bool)visible;
- (void)setVisibleMan:(bool)visible;
@end
