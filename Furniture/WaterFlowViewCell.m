//
//  WaterFlowViewCell.m
//  WaterFlowViewDemo
//
//  Created by Smallsmall on 12-6-11.
//  Copyright (c) 2012年 activation group. All rights reserved.
//

#import "WaterFlowViewCell.h"

@implementation WaterFlowViewCell
@synthesize columnCount = _columnCount;
@synthesize indexPath = _indexPath;
@synthesize strReuseIndentifier = _strReuseIndentifier;

-(id)initWithIdentifier:(NSString *)indentifier
{
	if(self = [super init])
	{
		self.strReuseIndentifier = indentifier;
	}
	
	return self;
}

-(void)relayoutViews{

    
}

- (void)dealloc
{
	self.indexPath = nil;
	self.strReuseIndentifier = nil;
}

@end


@implementation IndexPath
@synthesize row = _row,column = _column;

+(IndexPath *)initWithRow:(int)indexRow withColumn:(int)indexColumn{

    IndexPath *indexPath = [[IndexPath alloc] init];
    indexPath.row = indexRow;
    indexPath.column = indexColumn;
    return indexPath; //autoRelease
}

@end