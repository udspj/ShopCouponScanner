//
//  zarBarViewController.h
//  ShopBack
//
//  Created by rongyi on 13-12-18.
//  Copyright (c) 2013年 dev. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZBarSDK.h"

@interface zarBarViewController : UIViewController<ZBarReaderDelegate,UIAlertViewDelegate>{
    
    NSString *urlstr;
    BOOL hasqrcode;
    NSArray *QRarray;
  
    
    ZBarReaderViewController *reader;
    
    ZBarImageScanner *scanner;
    UIImageView *qroverimg;
    BOOL isclose;
}

@end
