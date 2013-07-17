//
//  BaseService.h
//  Furniture0701
//
//  Created by li yajin on 13-7-17.
//  Copyright (c) 2013年 郭胜龙. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BaseService : NSObject
{
    NSURLConnection *connection;
    NSMutableData *connectionData;
}
@property (nonatomic,retain) NSURLConnection *connection;
@property (nonatomic,retain) NSMutableData *connectionData;
@end
