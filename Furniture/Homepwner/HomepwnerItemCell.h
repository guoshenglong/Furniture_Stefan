//
//  HomepwnerItemCell.h
//  Homepwner
//
//  Created by huzhengnan on 13-7-9.
//  Copyright (c) 2013年 huzhengnan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface HomepwnerItemCell : UITableViewCell{
    IBOutlet UIImageView *backGroundImage;
    IBOutlet UIImageView *centerImage;
    IBOutlet UIButton *likeBtn;
    IBOutlet UILabel *name;
    IBOutlet UILabel *describe;
    IBOutlet UILabel *price;
}
@property (weak, nonatomic) IBOutlet UIImageView *backGroundImage;
@property (weak, nonatomic) IBOutlet UIImageView *centerImage;
@property (weak, nonatomic) IBOutlet UIButton *likeBtn;
@property (weak, nonatomic) IBOutlet UILabel *name;
@property (weak, nonatomic) IBOutlet UILabel *describe;
@property (weak, nonatomic) IBOutlet UILabel *price;
- (IBAction)changeImage:(id)sender;
@end
