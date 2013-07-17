//
//  WaterFlowView.h
//  WaterFlowViewDemo
//
//  Created by Smallsmall on 12-6-11.
//  Copyright (c) 2012年 activation group. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "WaterFlowViewCell.h"

@protocol WaterFlowViewDataSource;
@protocol WaterFlowViewDelegate;
@class WaterFlowView;


@interface WaterFlowView : UIScrollView<UITableViewDelegate,UITableViewDataSource>{

    int _columnCount;   //列数
    int _cellsTotal;    //总的数据项
    float _cellWidth;   //每列的宽度

    UIActivityIndicatorView *activityViewLoad;
    NSMutableArray *tableviews;
    
    
    id<WaterFlowViewDelegate> __unsafe_unretained _waterFlowViewDelegate;
    id<WaterFlowViewDataSource> __unsafe_unretained _waterFlowViewDatasource;
}

@property (nonatomic,assign) int columnCount; 
@property (nonatomic,assign) int cellsTotal; 
@property (nonatomic,assign) float cellWidth;
@property (nonatomic,assign) id<WaterFlowViewDelegate> waterFlowViewDelegate;
@property (nonatomic,assign) id<WaterFlowViewDataSource> waterFlowViewDatasource;

- (void)reloadData;  
- (NSInteger)waterFlowView:(WaterFlowView *)waterFlowView numberOfRowsInColumn:(NSInteger)colunm;
-(void)relayoutDisplaySubviews;

@end

/*
 代理方法
 */
@protocol WaterFlowViewDelegate <NSObject>

@optional

/*
 返回每个cell的高度
*/
- (CGFloat)waterFlowView:(WaterFlowView *)waterFlowView heightForRowAtIndexPath:(IndexPath *)indexPath;


/*
    跟据参数indexPath的行列属性，定位哪行哪列被选中
 */
- (void)waterFlowView:(WaterFlowView *)waterFlowView didSelectRowAtIndexPath:(IndexPath *)indexPath;


//瀑布滑动到底部需要进行数据请求的委托通知
-(void)waterFlowView:(WaterFlowView *)waterFlowViewNeedReqeustData;
@end



/*
    数据源
*/
@protocol WaterFlowViewDataSource<NSObject>

@optional

/*
    配置每个cell的子视图，添加返回的视图到cell上
 */

- (UIView *)waterFlowView:(WaterFlowView *)waterFlowView cellForRowAtIndexPath:(IndexPath *)indexPath;

/*
    将cell上的子视图传出，方便自定义子视图的样式，实现个性化定制
 */
-(void)waterFlowView:(WaterFlowView *)waterFlowView  relayoutCellSubview:(UIView *)view withIndexPath:(IndexPath *)indexPath;


/*
    返回瀑布效果的列数
 */
- (NSInteger)numberOfColumsInWaterFlowView:(WaterFlowView *)waterFlowView;

/*
    返回cell的总数，每个cell的行号通过总数和列号来确定
 */
- (NSInteger)numberOfAllWaterFlowView:(WaterFlowView *)waterFlowView;

@end
