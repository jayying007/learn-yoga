//
//  TextViewController.m
//  learn-yoga
//
//  Created by janezhuang on 2022/4/25.
//

#import "TextViewController.h"
#import <YogaKit/UIView+Yoga.h>
#import "UIView+Frame.h"

@interface TextViewController ()

@end

@implementation TextViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    
    UIScrollView *scrollView = [[UIScrollView alloc] init];
    UILabel *textLabel1 = [[UILabel alloc] init];
    textLabel1.numberOfLines = 50;
    textLabel1.font = [UIFont systemFontOfSize:30];
    textLabel1.text = @"这是一段长文本\n冷咖啡离开了杯垫\n我忍住的情绪在很后面\n拼命想挽回的从前\n在我脸上依旧清晰可见\n最美的不是下雨天\n是曾与你躲过雨的屋檐\n回忆的画面 在荡着秋千\n梦开始不甜\n你说把爱渐渐放下会走更远\n又何必去改变 已错过的时间\n你用你的指尖阻止我说再见\n想象你在身边 在完全失去之前";
    [scrollView addSubview:textLabel1];
    
    UILabel *textLabel2 = [[UILabel alloc] init];
    textLabel2.numberOfLines = 50;
    textLabel2.font = [UIFont systemFontOfSize:30];
    textLabel2.textColor = UIColor.redColor;
    textLabel2.text = @"你说把爱渐渐放下会走更远\n或许命运的签 只让我们遇见\n只让我们相恋这一季的秋天\n飘落后才发现 这幸福的碎片\n要我怎么捡";
    [scrollView addSubview:textLabel2];
    
    UIView *emptyView = [[UIView alloc] init];
    [scrollView addSubview:emptyView];
    [self.view addSubview:scrollView];
    
    UILabel *descLabel = [[UILabel alloc] init];
    descLabel.font = [UIFont systemFontOfSize:16];
    descLabel.numberOfLines = 2;
    descLabel.text = @"这是一段比较短的文本，固定在底部";
    [self.view addSubview:descLabel];
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    [button setTitle:@"确认收到" forState:UIControlStateNormal];
    [self.view addSubview:button];
    
    //======layout======
    [self.view configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.flexDirection = YGFlexDirectionColumn;
        layout.alignItems = YGAlignCenter;
        layout.padding = YGPointValue(16);
    }];
    [scrollView configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.flexGrow = 1;
        layout.flexShrink = 1;
        layout.flexDirection = YGFlexDirectionColumn;
        layout.width = YGPointValue(self.view.width);
        layout.alignItems = YGAlignCenter;
    }];
    [textLabel1 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.flexGrow = 1;
        layout.flexShrink = 0;
    }];
    [textLabel2 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.flexGrow = 1;
        layout.flexShrink = 0;
    }];
    [emptyView configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.flexGrow = 100;
        layout.flexShrink = 100;
    }];
    [descLabel configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.marginVertical = YGPointValue(8);
        layout.height = YGPointValue(120);
    }];
    [button configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.paddingVertical = YGPointValue(32);
        layout.minHeight = YGPointValue(40 + [self.view safeAreaInsets].bottom);
    }];
    
    [self.view.yoga applyLayout];
    scrollView.contentSize = CGSizeMake(scrollView.contentSize.width, textLabel1.height + textLabel2.height);
}

@end
