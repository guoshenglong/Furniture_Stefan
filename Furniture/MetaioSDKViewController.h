//
//  UnifeyeMobileViewController.h
//  metaio SDK
//
// Copyright 2007-2013 metaio GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <metaioSDK/IMetaioSDKIOS.h>

namespace metaio
{
    class IMetaioSDKIOS;     // forward declaration
    class IGeometry;   // forward declaration
    class ISensorsComponent;        // forward declaration
}

@class EAGLView;        // forward declaration
@class EAGLContext;     // forward declaration
@class CADisplayLink;   // forward declaration

@interface MetaioSDKViewController : UIViewController <MetaioSDKDelegate>
{	
    metaio::IMetaioSDKIOS*	m_metaioSDK;			//!< Reference to metaio SDK
    metaio::ISensorsComponent*		m_sensors;			//!< Pointer to our sensors manager
    
    
    // OpenGL related members (directly taken from XCode4 OpenGL example)
    EAGLContext *context;               // our OpenGL Context
    BOOL animating;                     // are we currently animating
    NSInteger animationFrameInterval;   // refresh interval
    CADisplayLink *displayLink;         // pointer to our displayLink

    EAGLView *glView;                   // our OpenGL View
}



@property (nonatomic, retain) IBOutlet EAGLView *glView;
@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;
@property (nonatomic, retain) IBOutlet UIButton *closeButton;

/** Close the current view again */
- (IBAction)onBtnClosePushed:(id)sender;

/** Start the OpenGL Animation */
- (void)startAnimation;

/** Stop the OpenGL Animation */
- (void)stopAnimation;

/** Called on every frame */
- (void)drawFrame;

@end

