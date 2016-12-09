//
//  zarBarViewController.m
//  ShopBack
//
//  Created by rongyi on 13-12-18.
//  Copyright (c) 2013年 dev. All rights reserved.
//

#import "zarBarViewController.h"
#import "AppController.h"
#include "CouponDetailScene.h"

@interface zarBarViewController ()

@end

@implementation zarBarViewController


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
-(void)viewDidAppear:(BOOL)animated{
    
    [super viewDidAppear:YES];
    
    
    //back to the new  view 
    if (!isclose) {
        [self presentViewController:reader animated:YES completion:Nil];
    }
    
    
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    isclose=NO;
    [self.navigationItem setTitle:@""];
    hasqrcode = NO;
    
    reader = [ZBarReaderViewController new];
    reader.readerDelegate = self;
    reader.view.frame=CGRectMake(50, 50, 50, 50);
    reader.supportedOrientationsMask = ZBarOrientationMaskAll;
    
    scanner = reader.scanner;
    
    [scanner setSymbology: ZBAR_I25 config: ZBAR_CFG_ENABLE to: 0];
    //[self presentViewController:reader animated:NO completion:nil];
    // add the overlayer
    qroverimg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"13-touming.png"]];
    qroverimg.frame = CGRectMake(0, 0, qroverimg.frame.size.width/2, qroverimg.frame.size.height/2);
    [reader.view addSubview:qroverimg];
}
- (void) imagePickerController: (UIImagePickerController*)reader didFinishPickingMediaWithInfo: (NSDictionary*) info
{
    if (hasqrcode) {
        return;
    }
    id<NSFastEnumeration> results = [info objectForKey: ZBarReaderControllerResults];
    ZBarSymbol *symbol = nil;
    for(symbol in results)
        break;
  
    urlstr = symbol.data;
    
    //判断是否包含 头'http:'
    NSString *regex = @"http+:[^\\s]*";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",regex];
    urlstr = symbol.data;
    
    
    NSLog(@"????????????erwimaxinxi ??%@",urlstr);
    if ([predicate evaluateWithObject:urlstr]) {
        NSLog(@"%@",urlstr);
        NSPredicate *p = [NSPredicate predicateWithFormat:@"SELF CONTAINS %@",@"www.rongyi.com"];
        NSPredicate *p2 = [NSPredicate predicateWithFormat:@"SELF CONTAINS %@",@"test.rongyi.com"];
        QRarray = [urlstr componentsSeparatedByString:@"/"];
        NSPredicate *type = [NSPredicate predicateWithFormat: @"SELF IN { 'redeem_line_items' }"];
        if (([p evaluateWithObject:urlstr] || [p2 evaluateWithObject:urlstr]) && [QRarray count]==5 && [type evaluateWithObject:[QRarray objectAtIndex:3]]) {
            NSLog(@"二维码的所有信息 %@",QRarray);
            //http://www.rongyi.com/redeem_line_items/aaaaaa
            
            isclose=YES;
            [reader dismissViewControllerAnimated:YES completion:^(void){
                [self dismissViewControllerAnimated:YES completion:^(void){
                    NSLog(@"cccccooommmpletetetetet");
                    Scene* scene = CCScene::create();
                    CouponDetail *layer = CouponDetail::create();
                    //layer->couponcode = couponinfo;
                    layer->getUseCouponData();
                    scene->addChild(layer);
                    Director::getInstance()->pushScene(TransitionSlideInR::create(0.3, scene));
                }];
            }];
            
        }else{
            UIAlertView *alert=[[UIAlertView alloc]initWithTitle:Nil message:@"无法识别的二维码" delegate:nil cancelButtonTitle:@"确认" otherButtonTitles:nil, nil];
            [alert show];
        }
    }
}
-(void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    isclose=YES;
    [picker dismissViewControllerAnimated:YES completion:^(void){
        [self dismissModalViewControllerAnimated:YES];
    }];
    //[self.navigationController popViewControllerAnimated:NO];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
