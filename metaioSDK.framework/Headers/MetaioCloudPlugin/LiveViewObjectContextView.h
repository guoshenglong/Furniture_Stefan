//
//  LiveViewObjectContextView.h
//  Junaio
//
//  Created by Stefan Misslinger
//  Copyright 2013 metaio. All rights reserved.
//

#import <UIKit/UIKit.h>

namespace metaio {
    namespace world
    {
        class MetaioWorldPOI;   // fwd decl.
    }
}

@protocol LiveViewObjectContextViewDelegate
- (void) contextViewButtonClosePushed;
- (void) onHandleURL:(NSString*) url;
@end


@interface LiveViewObjectContextView : UIView 
{
	const metaio::world::MetaioWorldPOI*       m_pPoi;

    NSObject<LiveViewObjectContextViewDelegate>* delegate;
}

@property (nonatomic, assign ) IBOutlet NSObject<LiveViewObjectContextViewDelegate>* delegate;

@property( nonatomic, retain)  IBOutlet	UILabel*            lblTitle;
@property( nonatomic, retain)  IBOutlet	UILabel*            lblSubitle;

@property( nonatomic, retain)  IBOutlet	UIView*             contentView;

@property( nonatomic, retain)  IBOutlet	UIButton*			actionButton1;
@property( nonatomic, retain)  IBOutlet	UIButton*			actionButton2;
@property( nonatomic, retain)  IBOutlet	UIButton*			actionButton3;
@property( nonatomic, retain)  IBOutlet	UIButton*			actionButton4;
@property( nonatomic, retain)  IBOutlet	UIButton*			actionButton5;

@property (nonatomic, retain) IBOutlet UIButton*                            btnClose;

@property( nonatomic, retain)  IBOutlet	UITextView*					txtContent;
@property( nonatomic, retain)  IBOutlet	UIImageView*				imageView;

- (IBAction) buttonClosePressed;

- (void) setPOI:(const metaio::world::MetaioWorldPOI*) poi;
- (void) closeIfContainsPOI: (const metaio::world::MetaioWorldPOI*) poi;

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration;
- (void) didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation;
@end
