//
//  BNRItemStore.m
//  Homepwner
//
//  Created by huzhengnan on 13-7-8.
//  Copyright (c) 2013年 huzhengnan. All rights reserved.
//

#import "BNRItemStore.h"
#import "BNRItem.h"

@implementation BNRItemStore


- (id)init
{
    self = [super init];
    if (self) {
        allItems = [[NSMutableArray alloc] init];
    }
    return self;
}

- (NSArray *)allItems
{
    return allItems;
}
- (BNRItem *)createItem
{
    BNRItem *p = [BNRItem randomItem];
    
    [allItems addObject:p];
    
    return p;
}

+ (BNRItemStore *)sharedStore
{
    static BNRItemStore *sharedStore = nil;
    if (!sharedStore) {
        sharedStore = [[super allocWithZone:nil] init];
    }
    return sharedStore;
}
+ (id)allocWithZone:(NSZone *)zone
{
    return [self sharedStore];
}

- (void)removeItem:(BNRItem *)p
{
    [allItems removeObjectIdenticalTo:p];
}

- (void)moveItemAtIndex:(int)form toIndex:(int)to
{
    if (form == to) {
        return;
    }
    BNRItem *p = [allItems objectAtIndex:form];
    [allItems removeObjectAtIndex:form];
    [allItems insertObject:p atIndex:to];
}

@end
