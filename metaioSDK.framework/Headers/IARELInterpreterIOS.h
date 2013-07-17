// Copyright 2007-2013 metaio GmbH. All rights reserved.
#ifndef _AS_IARELINTERPRETERIOS_
#define _AS_IARELINTERPRETERIOS_

#include "IARELInterpreter.h"
#include <Foundation/Foundation.h>

// forward declaration
@class UIWebView;
@class UIViewController;

/** Delegate to handle AREL callbacks
 */
@protocol IARELInterpreterIOSDelegate <NSObject>

@optional
/** The implementation should play a video from a given URL
 * \param videoURL the url to the video
 * \return void
 */
-(bool) playVideo:(NSString*) videoURL;

/**
 * \param url the url to the website
 * \param openInExternalApp true to open in external app, false otherwise
 * \return void
 */
-(bool) openWebsiteWithUrl:(NSString*) url inExternalApp:(bool) openInExternalApp;

/**
 * This is triggered as soon as the SDK is ready, e.g. splash screen is finished.
 */
-(void) onSDKReady;

/**
 * Called after scene options were loaded from AREL XML file (always called even if there are no
 * scene options)
 */
-(void) onSceneOptionsParsed:(const metaio::stlcompat::Vector<metaio::ARELSceneOption>&) sceneOptions;

/**
* This is triggered as soon as the AREL is ready, including the loading of XML geometries. 
*/
-(void) onSceneReady;


@end

namespace metaio
{
    /** Specialized class for iOS to register delegates
     */
    class IARELInterpreterIOS : public virtual IARELInterpreter
    {
    public:
        
        /** \brief Destructor
         */
        virtual ~IARELInterpreterIOS() {};
        
        /** \brief Register the delegate object that will receive callbacks
         * \param delegate the object
         * \return void
         */
        virtual void registerDelegate( NSObject<IARELInterpreterIOSDelegate>* delegate ) = 0;
    };
    
/**
* Create a IARELInterpreter for IOS
*
*	This functions should be only called on iOS platforms
*
* \param webView provide a UIWebView whre AREL is attached to
* \return IARELInterpreter an pointer to the created IARELInterpreter
*/
IARELInterpreterIOS* CreateARELInterpreterIOS(UIWebView* webView, UIViewController* viewController);
}

#endif
