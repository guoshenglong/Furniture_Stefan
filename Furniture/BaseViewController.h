//
//  BaseViewController.h
//  LBShopMall
//
//  Created by 李成武 on 13-3-22.
//  Copyright (c) 2013年 联龙博通在线服务中心.李成武. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "WaitView.h"

@interface BaseViewController : UIViewController<UIGestureRecognizerDelegate,WaitViewDelegate>

-(void)baseButtonClick:(UIButton *)button;
- (void)showBackBar;
- (void)showSearchBar;
- (void)showShareBar;
- (void)showTitle:(NSString *)title;
- (void)showImageName:(NSString *)name  isShow :(BOOL)animaed;


//停止隐藏加载转圈
-(void)showLoadingView;//将加载图放到最顶上
-(void)hideLoadingView;

//出错后显示错误提示图
-(void)showErrorView;
-(void)errorViewTappedGesture:(UITapGestureRecognizer *)gesture;//网络加载视图点击

@end
