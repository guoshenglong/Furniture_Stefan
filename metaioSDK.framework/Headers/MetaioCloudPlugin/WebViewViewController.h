//
//  WebViewViewController.h
//  Junaio
//
//  Created by Stefan Misslinger on 10/5/09.
//  Copyright 2009 metaio, Inc.. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MetaioViewControllerClosingCallback.h"

typedef void (^WebViewViewControllerCallbackBlock)(void);

@interface WebViewViewController : UIViewController<MetaioViewControllerClosingCallback,UIWebViewDelegate> {

    UIWebView*		webView;
    UIButton*		btnClose;
	
	NSURL*                              m_url;
    UIActivityIndicatorView *           activityIndicator;
    UIInterfaceOrientation              m_currentInterfaceOrientation;
}
@property (nonatomic, copy) MetaioActionBlock viewDidDisappearAction;

@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *activityIndicator;

@property (nonatomic, retain) IBOutlet UIWebView*		webView;
@property (nonatomic, retain) IBOutlet UIButton*		btnClose;

- (IBAction) buttonClose;

-(id) initializeWithURL: (NSString*) url;

@end
