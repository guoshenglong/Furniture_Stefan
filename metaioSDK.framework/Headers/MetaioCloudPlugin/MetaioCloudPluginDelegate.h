//
//  MetaioCloudPluginDelegate.h
//  MetaioCloudPlugin
//
//  Created by Stefan Misslinger.
//  Copyright 2013 metaio, Inc. All rights reserved.
//

@protocol MetaioCloudPluginDelegate

/** 
 * Provide the channel number that should be opened by the plugin 
 */
- (NSInteger) getChannelID;


@optional

/** Optional
 *
 * return filter values here that will be transmitted to your channel
 */
- (NSDictionary*) getFilterValues;


/** Optional
 *
 * return YES if the application should activate location sensors at startup
 * This will cause the application requesting permission at startup
 * Return YES here if you are using a location based channel that needs location at startup
 * Returning NO will cause the request to the server having no location
 */
- (BOOL) shouldUseLocationAtStartup;

/** Optional
 *
 * return YES if the application should support location
 * If you return NO here, your application will never access the location sensors.
 * Most scan channels don't need a location, so NO can be returned here.
 */
- (BOOL) shouldUseLocation;


/** Optional
 *
 * return YES to cache downloaded files
 * During the development phase it makes sense to return NO here,
 * if the channel content changes a lot.
 */
- (BOOL) shouldUseCache;


@end