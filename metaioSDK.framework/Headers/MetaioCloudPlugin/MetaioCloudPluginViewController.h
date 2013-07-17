//
//  MetaioCloudPluginViewController.h
//  Version 4.7
//
//  Created by Stefan Misslinger.
//  Copyright 2013 metaio, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <vector>
#include <MetaioSDK/TrackingValues.h>

#import "LiveViewInterfaceController.h"
#import "MetaioCloudPluginDelegate.h"


static const int ANCHOR_NONE =			0<<0;			///< No anchor, i.e. not relative-to-screen (0)
static const int ANCHOR_LEFT =			1<<0;			///< Anchor to the left edge (1)
static const int ANCHOR_RIGHT =			1<<1;			///< Anchor to the right edge (2)
static const int ANCHOR_BOTTOM =		1<<2;			///< Anchor to the bottom edge (4)
static const int ANCHOR_TOP =			1<<3;			///< Anchor to the top edge (8)
static const int ANCHOR_CENTER_H =		1<<4;			///< Anchor to the horizontal center (16)
static const int ANCHOR_CENTER_V =		1<<5;			///< Anchor to the vertical center (32)

static const int ANCHOR_TL = ANCHOR_LEFT|ANCHOR_TOP;				///< Anchor to the Top-Left (9)
static const int ANCHOR_TC = ANCHOR_TOP|ANCHOR_CENTER_H;			///< Anchor to the Top-Center (24)
static const int ANCHOR_TR = ANCHOR_TOP|ANCHOR_RIGHT;				///< Anchor to the Top-Right (10)
static const int ANCHOR_CL = ANCHOR_CENTER_V|ANCHOR_LEFT;			///< Anchor to the Center-Left (33)
static const int ANCHOR_CC = ANCHOR_CENTER_H|ANCHOR_CENTER_V;		///< Anchor to the Center (48)
static const int ANCHOR_CR = ANCHOR_CENTER_V|ANCHOR_RIGHT;			///< Anchor to the Center-Right (34)
static const int ANCHOR_BL = ANCHOR_BOTTOM|ANCHOR_LEFT;				///< Anchor to the Bottom-Left (5)
static const int ANCHOR_BC = ANCHOR_BOTTOM|ANCHOR_CENTER_H;			///< Anchor to the Bottom-Center (20)
static const int ANCHOR_BR = ANCHOR_BOTTOM|ANCHOR_RIGHT;			///< Anchor to the Bottom-Right (6)


@interface MetaioCloudPluginViewController : LiveViewInterfaceController<MetaioCloudPluginDelegate>


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


/** Informs the application when loading has been completed
 * Note: make sure to call [super onSceneReady] when overwriting this method
 */
- (void)  onSceneReady;


/** Callback to inform the client that visiblity has changed
 * \param visiblity new visibility
 */
-(void) onRadarVisibilityChanged: (BOOL) visiblity;


/** Open the sharing controller for a certain image
 * \param imageToShare the image to share.
 */
- (void) openSharingViewController: (UIImage*) imageToShare;


/**
 * \brief Callback that informs new pose states (tracked, detected or lost)
 *
 * This is called automatically as soon as poses have been updated. The vector
 * contains all the valid poses.
 * The invalid pose is only returned for first frame as soon as target is lost
 * to inform this event.
 * Note that this function is called in rendering thread, thus it would block
 * rendering. It should be returned as soon as possible wihout any expensive
 * processing.
 *
 * \param poses current valid poses
 *
 */
- (void) onTrackingEvent: (const metaio::stlcompat::Vector<metaio::TrackingValues>&)poses;


@end
