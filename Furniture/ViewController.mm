//
//  ViewController.m
//  Furniture0701
//
//  Created by 郭胜龙 on 13-7-1.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import "ViewController.h"
#import "EAGLView.h"


@interface ViewController ()

@end

@implementation ViewController
@synthesize subview;

// gesture masks to specify which gesture(s) is enabled
//int GESTURE_DRAG = 1<<0;
//int GESTURE_ROTATE = 2<<0;
//int GESTURE_PINCH = 4<<0;
//int GESTURE_ALL = 0xFF;

#pragma - UIViewController lifecycle


- (void) viewDidLoad
{
    [super viewDidLoad];
    
        
    // make the subview transparent（让subView透明）
    subview.backgroundColor = [UIColor clearColor];
    
    m_gestures = 0xFF; //enables all gestures（开启所有的手势）
    m_gestureHandler = [[GestureHandlerIOS alloc] initWithSDK:m_metaioSDK withView:glView withGestures:m_gestures];
    
    m_imageTaken = false;
    
    // load our tracking configuration（加载跟踪配置信息）
    bool success = m_metaioSDK->setTrackingConfiguration("ORIENTATION_FLOOR");
    NSLog(@"ORIENTATION tracking has been loaded: %d", (int)success);
    
    
    // load content（加载内容）
    // load metaio man（）
    NSString* manPath = [[NSBundle mainBundle] pathForResource:@"metaioman" ofType:@"md2" inDirectory:@"Assets7"];
    
	if(manPath)
	{
		// if this call was successful, m_metaioMan will contain a pointer to the 3D model
        m_metaioMan =  m_metaioSDK->createGeometry([manPath UTF8String]);
        if(m_metaioMan)
        {
            // scale it a bit up
            m_metaioMan->setScale(metaio::Vector3d(5.0,5.0,5.0));
            // add it to the gesture handler.
            [m_gestureHandler addObject:m_metaioMan andGroup:1];
        }
        else
        {
            NSLog(@"Error loading the metaio man model: %@", manPath);
        }
    }
    // hide the metaio man at the beginning
    [self setVisibleMan:false];
    
    // load chair
    NSString* chairPath = [[NSBundle mainBundle] pathForResource:@"stuhl" ofType:@"obj" inDirectory:@"Assets7"];
    if (chairPath)
    {
        m_chair = m_metaioSDK->createGeometry([chairPath UTF8String]);
        if (m_chair)
        {
            //这个方法并不是设置它的初始大小，而是设置它的最大大小
            m_chair->setScale(metaio::Vector3d(50.0, 50.0, 50.0));
            //rotate the chair to be upright
            m_chair->setRotation(metaio::Rotation(M_PI_2, 0.0, 0.0));
            m_chair->setTranslation(metaio::Vector3d(0.0, 0.0, 0.0));
            [m_gestureHandler addObject:m_chair andGroup:2];
        }
        else
        {
            NSLog(@"Error loading the chair: %@", chairPath);
        }
    }
    [self setVisibleChair:false];
    
    // load tv
    NSString* tvPath = [[NSBundle mainBundle] pathForResource:@"tv" ofType:@"obj" inDirectory:@"Assets7"];
    if (tvPath)
    {
        m_tv = m_metaioSDK->createGeometry([tvPath UTF8String]);
        if (m_tv)
        {
            m_tv->setScale(metaio::Vector3d(50.0, 50.0, 50.0));
            m_tv->setRotation(metaio::Rotation(M_PI_2, 0.0, -M_PI_2));
            m_tv->setTranslation(metaio::Vector3d(0.0, 10.0, 0.0));
            [m_gestureHandler addObject:m_tv andGroup:3];
        }
        else
        {
            NSLog(@"Error loading the TV: %@", tvPath);
        }
    }
    
    // load screen
    NSString* screenPath = [[NSBundle mainBundle] pathForResource:@"screen" ofType:@"obj" inDirectory:@"Assets7"];
    if (screenPath)
    {
        m_screen = m_metaioSDK->createGeometry([screenPath UTF8String]);
        if (m_screen)
        {
            m_screen->setScale(metaio::Vector3d(50.0, 50.0, 50.0));
            m_screen->setRotation(metaio::Rotation(M_PI_2, 0.0, -M_PI_2));
            m_screen->setTranslation(metaio::Vector3d(0.0, 10.0, 0.0));
			
			// set the screen to the same group as the TV since it should be scaled/moved/rotated the same way as the TV is
            [m_gestureHandler addObject:m_screen andGroup:3];
            
            // start the movie
            NSString* moviePath = [[NSBundle mainBundle] pathForResource:@"sintel" ofType:@"3g2" inDirectory:@"Assets7"];
            m_screen->setMovieTexture([moviePath UTF8String]);
        }
        else
        {
            NSLog(@"Error loading the screen: %@", screenPath);
        }
    }
    [self setVisibleTV:false];
    
    // set button images to each state
    for (UIView* subView in self.view.subviews)
    {
        if ([subView isKindOfClass:[UIButton class]])
        {
            //下面两句首先将subView转换为UIButton类型，然后获得button的title；
            UIButton* button = (UIButton*) subView;
            NSString* title = button.currentTitle;
            //通过title值的不同来确定不同的button图形
            if ([title isEqual:@"TV"])
            {
                [button setSelected:false];
                [button setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"button_tv_unselected" ofType:@"png" inDirectory:@"Assets7"]] forState:UIControlStateNormal];
                [button setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"button_tv_selected" ofType:@"png" inDirectory:@"Assets7"]] forState:UIControlStateSelected];
            }
            else if ([title isEqual:@"Chair"])
            {
                [button setSelected:false];
                [button setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"button_chair_unselected" ofType:@"png" inDirectory:@"Assets7"]] forState:UIControlStateNormal];
                [button setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"button_chair_selected" ofType:@"png" inDirectory:@"Assets7"]] forState:UIControlStateSelected];
            }
            else if ([title isEqual: @"metaioMan"])
            {
                [button setSelected:false];
                [button setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"button_man_unselected" ofType:@"png" inDirectory:@"Assets7"]] forState:UIControlStateNormal];
                [button setImage:[UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"button_man_selected" ofType:@"png" inDirectory:@"Assets7"]] forState:UIControlStateSelected];
            }
        }
    }
	

}


#pragma mark - Rotation handling


- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)InterfaceOrientation
{
    // allow rotation in all directions
    return YES;
}

- (void)drawFrame
{
    [super drawFrame];
    //当照相机拍照之后会通过下面加载机器人的跟踪配置信息
    // load the dummy tracking config file once a camera image has been taken and move the geometries to a certain location on the screen
    if (m_imageTaken)
    {
        bool result = m_metaioSDK->setTrackingConfiguration("DUMMY");
        NSLog(@"Tracking data dummy loaded: %d", (int)result);
        
		// set the previously loaded pose
        //导入先前机器人的数据
		m_metaioSDK->setCosOffset(1, m_pose);
        
        m_imageTaken = false;
    }
}

#pragma mark - @protocol MobileDelegate

- (void) onAnimationEnd: (metaio::IGeometry*) geometry  andName:(NSString*) animationName
{
    // handle the metaio man animations
    if( geometry == m_metaioMan )
    {
        // check the previous animation name and act accordingly
        if( [animationName compare:@"shock_down"] == NSOrderedSame )
        {
            geometry->startAnimation( "shock_idle" , false);
        }
        else if( [animationName compare:@"shock_idle"] == NSOrderedSame  )
        {
            geometry->startAnimation( "shock_up" , false);
        }
        else if( [animationName compare:@"close_down"] == NSOrderedSame )
        {
            geometry->startAnimation( "close_idle", true);
        }
    }
    
}

#pragma mark - Handling Touches

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    // record the initial states of the geometries with the gesture handler
    //记录开始手势前3D模型的状态
    [m_gestureHandler touchesBegan:touches withEvent:event withView:glView];
    
    // Here's how to pick a geometry
    //获取触碰对象
	UITouch *touch = [touches anyObject];
    //记录下它在屏幕上的坐标
	CGPoint loc = [touch locationInView:glView];
	
    // get the scale factor (will be 2 for retina screens)
    //记录下缩放因子
    float scale = glView.contentScaleFactor;
    
	// ask sdk if the user picked an object（返回在loc坐标下的3D模型）
	// the 'true' flag tells sdk to actually use the vertices for a hit-test, instead of just the bounding box
    //如果第三个参数是true，那么将采用定点测定法测定触碰物体，false则为以矩形测定；
    metaio::IGeometry* model = m_metaioSDK->getGeometryFromScreenCoordinates(loc.x * scale, loc.y * scale, false);
	
    if (model == m_metaioMan)
	{
		// we have touched the metaio man
		// let's start an animation
		model->startAnimation( "shock_down" , false);
	}
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    // handles the drag touch
    [m_gestureHandler touchesMoved:touches withEvent:event withView:glView];
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    [m_gestureHandler touchesEnded:touches withEvent:event withView:glView];
}

// handles the reactions from touching the geometry buttons. it not only show/hide the geometries, it also resets the location and the scale
//模型选择按钮的实现，包括每次重置它的位置和缩放
- (IBAction)onTVButtonClick:(id)sender
{
    //这一步很关键，将sender转化为button类型
    UIButton* button = (UIButton*)sender;
    // if the button is already selected, change its state to unselected, and hide the geometry
    //这里是将button设置成为双色跳变的模式，selected是button本身的属性
    if ([button isSelected])
    {
        button.selected = false;
        [self setVisibleTV:false];
    }
    else
    {
        button.selected = true;
        [self setVisibleTV:true];
        
        // reset the location of the geometry
        //重置3D模型的方位
        CGRect screen = self.view.bounds;
        CGFloat width = screen.size.width * [UIScreen mainScreen].scale;
        CGFloat height = screen.size.height * [UIScreen mainScreen].scale;
        metaio::Vector3d translation = m_metaioSDK->get3DPositionFromScreenCoordinates(1, metaio::Vector2d(width/2, height/2));
        m_tv->setTranslation(translation);
        m_screen->setTranslation(translation);
		
		m_screen->startMovieTexture();
        
        // reset the scale of the geometry
        m_tv->setScale(metaio::Vector3d(50.0, 50.0, 50.0));
        m_screen->setScale(metaio::Vector3d(50.0, 50.0, 50.0));
    }
}

- (IBAction)onChairButtonClick:(id)sender
{
    UIButton* button = (UIButton*)sender;
    if ([button isSelected])
    {
        button.selected = false;
        [self setVisibleChair:false];
    }
    else
    {
        button.selected = true;
        [self setVisibleChair:true];
        
        CGRect screen = self.view.bounds;
        CGFloat width = screen.size.width * [UIScreen mainScreen].scale;
        CGFloat height = screen.size.height * [UIScreen mainScreen].scale;
        metaio::Vector3d translation = m_metaioSDK->get3DPositionFromScreenCoordinates(1, metaio::Vector2d(width/2, height/2));
        
        
        m_chair->setTranslation(translation);
        //重置一下缩放，但是旋转角度没有重置
        m_chair->setScale(metaio::Vector3d(50.0, 50.0, 50.0));
    }
}

- (IBAction)onManButtonClick:(id)sender
{
    UIButton* button = (UIButton*)sender;
    if ([button isSelected])
    {
        button.selected = false;
        [self setVisibleMan:false];
    }
    else
    {
        button.selected = true;
        [self setVisibleMan:true];
        
        CGRect screen = self.view.bounds;
        CGFloat width = screen.size.width * [UIScreen mainScreen].scale;
        CGFloat height = screen.size.height * [UIScreen mainScreen].scale;
        metaio::Vector3d translation = m_metaioSDK->get3DPositionFromScreenCoordinates(1, metaio::Vector2d(width/2, height/2));
        
        m_metaioMan->setTranslation(translation);
        m_metaioMan->setScale(metaio::Vector3d(5.0, 5.0, 5.0));
    }
}

// take picture button pressed.
- (IBAction)onTakePicture:(id)sender
{
    //获取设备应用程序主目录的路径
    NSString* dir = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString* filePath = [NSString stringWithFormat:@"%@/targetImage.jpg", dir];
    m_metaioSDK->requestCameraImage([filePath UTF8String]);
    //    m_metaioSDK->requestCameraImage();
}

// save screenshot button pressed
- (IBAction)onSaveScreen:(id)sender
{
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString* publicDocumentsDir = [paths objectAtIndex:0];
    
    NSError* docerror;
    NSArray* files = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:publicDocumentsDir error:&docerror];
    if (files == nil)
    {
        NSLog(@"Error reading contents of documents directory: %@", [docerror localizedDescription]);
    }
    
    
    NSString* timeStamp = [NSString stringWithFormat:@"%ld", (long)[[NSDate date] timeIntervalSince1970]];
    NSString* fileName = [NSString stringWithFormat:@"%@.jpg", timeStamp];
    NSString* fullPath = [publicDocumentsDir stringByAppendingPathComponent:fileName];
    
    
    m_metaioSDK->requestScreenshot([fullPath UTF8String], glView->defaultFramebuffer, glView->colorRenderbuffer);
    //    m_metaioSDK->requestScreenshot(glView->defaultFramebuffer, glView->colorRenderbuffer);
    NSLog(@"framebuffer = %d",glView->defaultFramebuffer);
    
    // generate an alert to notify the user of screenshot saving
    UIAlertView *message = [[UIAlertView alloc] initWithTitle:@"ATTENTION"
                                                      message:@"The screenshot has been saved to the document folder."
                                                     delegate:nil
                                            cancelButtonTitle:@"OK"
                                            otherButtonTitles:nil];
    [message show];
}

// reset the app -- reactivate the camera, hide the geometries and change the button state (selected) from true to false
- (IBAction)onClearScreen:(id)sender
{
    // reactivate the camera（重启相机）
    m_metaioSDK->startCamera(0);
    
    // reload the orientation tracking config file（重新载入跟踪配置信息）
    bool success = m_metaioSDK->setTrackingConfiguration("ORIENTATION_FLOOR");
    NSLog(@"ORIENTATION tracking has been loaded: %d", (int)success);
    
    [self setVisibleTV:false];
    [self setVisibleChair:false];
    [self setVisibleMan:false];
    
    // reset the button images to "unselected"（重置按钮到为选择状态）
    for (UIView* subView in self.view.subviews)
    {
        if ([subView isKindOfClass:[UIButton class]])
        {
            UIButton* button = (UIButton*) subView;
            NSString* title = button.currentTitle;
            if ([title isEqual:@"TV"])
            {
                button.selected = false;
            }
            else if ([title isEqual:@"Chair"])
            {
                button.selected = false;
            }
            else if ([title isEqual: @"metaioMan"])
            {
                button.selected = false;
            }
        }
    }
}

// hide/show the geometries
- (void)setVisibleTV:(bool)visible
{
    if (m_tv != NULL && m_screen != NULL)
    {
        m_tv->setVisible(visible);
        m_screen->setVisible(visible);
    }
    
    // remember to consider the movie
    if (visible)
    {
        m_screen->startMovieTexture();
    }
    else
    {
        m_screen->stopMovieTexture();
    }
}

- (void)setVisibleChair:(bool)visible
{
    if (m_chair != NULL)
    {
        m_chair->setVisible(visible);
    }
}

- (void)setVisibleMan:(bool)visible
{
    if (m_metaioMan != NULL)
    {
        m_metaioMan->setVisible(visible);
    }
}

// set the camera image as the tracking target（将拍摄的照片设为跟踪目标）
- (void) onCameraImageSaved: (NSString*) filepath
{
    if (filepath.length > 0)
    {
        m_metaioSDK->setImage([filepath UTF8String]);
    }
    m_imageTaken = true;
	
	//remember the current pose
	m_pose = m_metaioSDK->getTrackingValues(1);
    
}

- (void) onNewCameraFrame:(metaio::ImageStruct *)cameraFrame
{
    UIImage* image = m_metaioSDK->ImageStruct2UIImage(cameraFrame, true);
    UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);
}

-(void) onScreenshot:(NSString*) filepath
{
}

- (void) onScreenshotImageIOS:(UIImage *)image
{
    UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);
}

- (void)viewDidUnload {
    [self setSubview:nil];
    [super viewDidUnload];
}
@end
