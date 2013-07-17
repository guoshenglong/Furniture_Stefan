//
//  BNRItemStore.h
//  Homepwner
//
//  Created by huzhengnan on 13-7-8.
//  Copyright (c) 2013年 huzhengnan. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BNRItem;

@interface BNRItemStore : NSObject
{
    NSMutableArray *allItems;
}
+ (BNRItemStore *)sharedStore;

- (NSArray *)allItems;
- (BNRItem *)createItem;
- (void)removeItem:(BNRItem *)p;
- (void)moveItemAtIndex:(int)form toIndex:(int)to;
@end
