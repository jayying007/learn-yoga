//
//  ViewController.m
//  learn-yoga
//
//  Created by janezhuang on 2022/4/25.
//

#import "ViewController.h"
#import "TextViewController.h"
#import <YogaKit/UIView+Yoga.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    
    // Do any additional setup after loading the view.
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    NSLog(@"%.2f", [UIScreen mainScreen].scale);
    button.frame = CGRectMake(60, 300, 100, 50);
    [button setTitle:@"jump" forState:UIControlStateNormal];
    [button addTarget:self action:@selector(jump) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];
    
    UIView *view1 = [[UIView alloc] init];
    view1.backgroundColor = UIColor.redColor;
    [self.view addSubview:view1];
    
    [view1 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.flexDirection = YGFlexDirectionRow;
        layout.flexWrap = YGWrapWrap;
        layout.width = YGPointValue(200);
        layout.height = YGPointValue(100);
        layout.marginTop = YGPointValue(50);
        layout.marginHorizontal = YGPointValue(100);
        layout.justifyContent = YGJustifyFlexEnd;
    }];
    
    UIView *view2 = [[UIView alloc] init];
    view2.backgroundColor = UIColor.greenColor;
    [view1 addSubview:view2];
    
    [view2 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.width = YGPointValue(20);
        layout.height = YGPointValue(20);
        layout.marginHorizontal = YGPointValue(10);
    }];
    
    UIView *view3 = [[UIView alloc] init];
    view3.backgroundColor = UIColor.blueColor;
    [view1 addSubview:view3];
    
    [view3 configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.width = YGPointValue(20);
        layout.height = YGPointValue(20);
        layout.marginHorizontal = YGPointValue(10);
    }];
    
    [view1.yoga applyLayoutPreservingOrigin:YES];
    
    NSLog(@"%lu", (unsigned long)view1.yoga.numberOfChildren);
}

- (void)jump {
    TextViewController *vc = [[TextViewController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}
@end
