
#include "MainSelectScene.h"
#include "HelloWorldScene.h"

#include "ShowCouponsScene.h"
#include "CouponCodeScene.h"
#include "QRcheckScene.h"

#include "zarBarViewController.h"
#include "AppController.h"

USING_NS_CC;

Scene* MainSelect::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainSelect::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainSelect::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = Director::getInstance()->getVisibleOrigin();
    
    //大背景图片
    auto sprite = Sprite::create("background.png");
    sprite->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite);
    
    //顶部navigationbar图
    auto spritebar = Sprite::create("head.png");
    spritebar->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x,visibleSize.height + origin.y - spritebar->getContentSize().height/2));
    this->addChild(spritebar);
    
    //顶部navigationbar标题文本
    auto label = LabelTTF::create("容易逛商家后台", "Arial", 40);
    label->setPosition(cocos2d::Point(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label);
    
    //顶部navigationbar返回按钮
    auto backItem = MenuItemImage::create("navbackbg.png","navbackbg.png",CC_CALLBACK_1(MainSelect::gotoBack, this));
	backItem->setPosition(cocos2d::Point(origin.x+50, origin.y + visibleSize.height - label->getContentSize().height));
    auto backmenu = Menu::create(backItem, NULL);
    backmenu->setPosition(cocos2d::Point::ZERO);
    this->addChild(backmenu);

    
    //---------------------------------------------------------------------
    
    
    cocos2d::Size childsSize = cocos2d::Size(233*2, 33*2);
    float childsDis = 50.0;
    int childsNum = 3;
    float childsWholeHeight = childsSize.height * childsNum + childsDis * (childsNum - 1);
    
    auto btnselectimg1 = Scale9Sprite::create("btn1_big.png");
    auto btnnomarlimg1 = Scale9Sprite::create("btn2_big.png");
    auto label1 = LabelTTF::create("查询优惠券", "Marker Felt", 35);
    auto btn1 = ControlButton::create(label1, btnnomarlimg1);
    btn1->setPreferredSize(childsSize);
    btn1->setZoomOnTouchDown(false);
    btn1->setPosition(cocos2d::Point(visibleSize.width * 0.5, (visibleSize.height - childsWholeHeight + childsSize.height)*0.5 + (childsSize.height + childsDis) * 2));
    btn1->setBackgroundSpriteForState(btnselectimg1, Control::State::HIGH_LIGHTED);
    btn1->setTitleColorForState(Color3B(255, 255, 255), Control::State::HIGH_LIGHTED);
    btn1->addTargetWithActionForControlEvents(this, cccontrol_selector(MainSelect::gotoShowCoupons), Control::EventType::TOUCH_DOWN);
    this->addChild(btn1);
    
    auto btnselectimg2 = Scale9Sprite::create("btn1_big.png");
    auto btnnomarlimg2 = Scale9Sprite::create("btn2_big.png");
    auto label2 = LabelTTF::create("核销二维码", "Marker Felt", 35);
    auto btn2 = ControlButton::create(label2, btnnomarlimg2);
    btn2->setPreferredSize(childsSize);
    btn2->setZoomOnTouchDown(false);
    btn2->setPosition(cocos2d::Point(visibleSize.width * 0.5, (visibleSize.height - childsWholeHeight + childsSize.height)*0.5 + (childsSize.height + childsDis) * 1));
    btn2->setBackgroundSpriteForState(btnselectimg2, Control::State::HIGH_LIGHTED);
    btn2->setTitleColorForState(Color3B(255, 255, 255), Control::State::HIGH_LIGHTED);
    btn2->addTargetWithActionForControlEvents(this, cccontrol_selector(MainSelect::gotoQRcamera), Control::EventType::TOUCH_DOWN);
    this->addChild(btn2);
    
    auto btnselectimg3 = Scale9Sprite::create("btn1_big.png");
    auto btnnomarlimg3 = Scale9Sprite::create("btn2_big.png");
    auto label3 = LabelTTF::create("核销优惠码", "Marker Felt", 35);
    auto btn3 = ControlButton::create(label3, btnnomarlimg3);
    btn3->setPreferredSize(childsSize);
    btn3->setZoomOnTouchDown(false);
    btn3->setPosition(cocos2d::Point(visibleSize.width * 0.5, (visibleSize.height - childsWholeHeight + childsSize.height)*0.5 + (childsSize.height + childsDis) * 0));
    btn3->setBackgroundSpriteForState(btnselectimg3, Control::State::HIGH_LIGHTED);
    btn3->setTitleColorForState(Color3B(255, 255, 255), Control::State::HIGH_LIGHTED);
    btn3->addTargetWithActionForControlEvents(this, cccontrol_selector(MainSelect::gotoCouponsCode), Control::EventType::TOUCH_DOWN);
    this->addChild(btn3);

    return true;
}

void MainSelect::gotoShowCoupons(Object* pSender, Control::EventType controlEvent){
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.3, ShowCoupons::createScene()));
}
void MainSelect::gotoQRcamera(Object* pSender, Control::EventType controlEvent){
    CCLOG("Touch the Button");
    //Director::getInstance()->replaceScene(TransitionSlideInR::create(0.3, QRcheck::createScene()));
    
    zarBarViewController *testvc = [[zarBarViewController alloc] init];
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    [appController.viewController presentModalViewController:testvc animated:YES];
}
void MainSelect::gotoCouponsCode(Object* pSender, Control::EventType controlEvent){
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.3, CouponCode::createScene()));
}

void MainSelect::gotoBack(Object* pSender){
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.3, HelloWorld::createScene()));
}



