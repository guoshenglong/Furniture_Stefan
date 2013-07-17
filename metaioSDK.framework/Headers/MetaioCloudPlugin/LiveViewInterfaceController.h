//
// LiveViewInterfaceController.h
// Junaio
//
//  Created by Stefan Misslinger on 10/2/09.
//  Copyright 2013 metaio, Inc. All rights reserved.
//
#import "MetaioViewControllerClosingCallback.h"
#import "LiveViewObjectContextView.h"

// forward declarations
@class ASEAGLView;

@interface LiveViewInterfaceController : UIViewController
 <UINavigationControllerDelegate, UIWebViewDelegate, UIGestureRecognizerDelegate, LiveViewObjectContextViewDelegate>
{	
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

@property (nonatomic, retain) IBOutlet UILabel*                         messageActivityLabel;		// Label that
@property (nonatomic, retain) IBOutlet LiveViewObjectContextView*		objectContextView;
@property (nonatomic, retain) IBOutlet ASEAGLView*                        glView;
@property (nonatomic, retain) IBOutlet UIView*							interfaceView;
@property (nonatomic, retain) IBOutlet UIWebView*                       arelWebView;
@property (nonatomic, retain) IBOutlet UIProgressView*                  progressView;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView*			activityIndicator;


/** Removes all content and triggers a new pois search */
- (void) reloadCurrentChannel;


/** Override this method if you want to display your webviewcontroller in a different way */
- (void) presentContentViewController: (UIViewController<MetaioViewControllerClosingCallback>*) contentViewController;


/** Implementation to get a billboard image for a poi
 * \param poi the poi
 * \param image the thumbnail of the poi
 * \return the image
 */
- (UIImage*) getBillboardImageForPOI: (const metaio::world::MetaioWorldPOI*) poi withThumbnail: (UIImage*) image;


/** Overwrite this method to provide your own viewcontroller for displaying URLs
 * \param url the URL that should be openend
 * \return autoreleased viewcontroller
 *
 * You can use this method to provide your own WebviewController if desired
 */
- (UIViewController<MetaioViewControllerClosingCallback>*) getContentViewControllerForURL:(NSString*) url;


/** This method allows you to (re)set a channel ID that the plugin will use. Calling this method will cause a complete refresh (i.e. remove all objects and load POIs from the given channel ID again.
 *  Note, this Method will not query the delegate
 *
 * \param channelID the channel ID to set
 * \param filters the filter paramters that should be sent to your channel
 */
- (void) openChannelID:(int) channelID withFilterValues:(NSDictionary*) filters;


/** Returns the currenlty loaded channel ID
 * \return the currenlty loaded channel ID
 */
- (int) getCurrentChannelID;


/** Show an info message on the screen
 * \param message the message
 */
- (void) showInfoMessage: (NSString*) message;


/** Overwrite this method if you want to be able to handle custom URL schemes that are launched
 * from your channel
 * \param request the request that is being sent
 *
 * You can use it like this:
 * NSURL* theURL = [request mainDocumentURL];
 * NSString* absoluteString = [theURL absoluteString];
 * if( [[absoluteString lowercaseString] hasPrefix:@"yourapp://"] )
 * {
 *   // do something
 *   return NO;
 * }
 * return YES;
 */
- (BOOL) shouldStartLoadWithRequest:(NSURLRequest *) request;

/** Define the offset of the radar relative to the upper right corner
 * \param offset the offset in x/y
 * \param scale the relative scale of the radar
 * \param the anchor to set. (default: top-right: 10)
 */
- (void) setRadarOffset:(CGPoint) offset scale:(float) scale anchor:(int) anchor;

@end


@interface LiveViewInterfaceController (OpenGL)
- (void)startAnimation;
- (void)stopAnimation;
@end

