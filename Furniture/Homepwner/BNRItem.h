//
//  BNRItem.h
//  RandomPossessions
//
//  Created by joeconway on 7/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BNRItem : NSObject
{
}

+ (id)randomItem;

- (id)initWithItemName:(NSString *)name
           describtion:(NSString *)desc
           imagePath:(NSString *)img
        valueInDollars:(NSString *)value;

@property (nonatomic, strong) BNRItem *containedItem;
@property (nonatomic, weak) BNRItem *container;

@property (nonatomic, copy) NSString *itemName;
@property (nonatomic, copy) NSString *describe;
@property (nonatomic, copy) NSString *imagePath;
@property (nonatomic, copy) NSString *price;
@property (nonatomic) bool isLike;
@property (nonatomic, readonly, strong) NSDate *dateCreated;

@end
