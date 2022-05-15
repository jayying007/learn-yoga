//
//  ViewController.m
//  learn-yoga
//
//  Created by janezhuang on 2022/4/25.
//

#import "ViewController.h"
#import "TextViewController.h"
#import <YogaKit/UIView+Yoga.h>
#import "UIView+Frame.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    
    // Do any additional setup after loading the view.
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    button.frame = CGRectMake(60, 300, 100, 50);
    [button setTitle:@"jump" forState:UIControlStateNormal];
    [button addTarget:self action:@selector(jump) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];
    
    UIView *view1 = [[UIView alloc] init];
    view1.backgroundColor = UIColor.redColor;
    [self.view addSubview:view1];
    
        UIView *view2 = [[UIView alloc] init];
        view2.backgroundColor = UIColor.greenColor;
        [view1 addSubview:view2];
    
            UIView *view4 = [[UIView alloc] init];
            view4.backgroundColor = UIColor.whiteColor;
            [view2 addSubview:view4];
    
        UIView *view3 = [[UIView alloc] init];
        view3.backgroundColor = UIColor.blueColor;
        [view1 addSubview:view3];
    
    [view1 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.width = YGPointValue(200);
        layout.height = YGPointValue(100);
        layout.marginTop = YGPointValue(80);
        layout.marginHorizontal = YGPointValue(100);
        layout.paddingBottom = YGPointValue(10);
        layout.justifyContent = YGJustifyFlexEnd;
    }];
    [view2 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.width = YGPointValue(60);
        layout.padding = YGPointValue(8);
        layout.marginHorizontal = YGPointValue(10);
    }];
    [view3 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.width = YGPointValue(30);
        layout.height = YGPointValue(30);
        layout.marginHorizontal = YGPointValue(12);
        layout.alignSelf = YGAlignCenter;
    }];
    [view4 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.width = YGPointValue(20);
        layout.height = YGPointValue(20);
        layout.margin = YGPointValue(5);
        layout.flexGrow = 1;
    }];
    
    [view1.yoga applyLayout];
    NSLog(@"");
}

- (void)jump {
    TextViewController *vc = [[TextViewController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}
@end
