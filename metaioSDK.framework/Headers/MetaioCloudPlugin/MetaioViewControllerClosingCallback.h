//
//  MetaioViewControllerClosingCallback.h
//  MetaioCloudPlugin
//
//  Created by Stefan Misslinger.
//  Copyright 2013 metaio, Inc.. All rights reserved.
//


// Block that will perform an action
typedef void (^MetaioActionBlock)(void);

@protocol MetaioViewControllerClosingCallback

/** Set the block that will be executed on viewDidDisappear
 * In the metaio cloud plugin this is used to provide callbacks to the cloud plugin engine, that a webview or videoview has been closed.
 */
-(void) setViewDidDisappearBlock:(MetaioActionBlock) block;

@end
