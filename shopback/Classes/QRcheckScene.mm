
#include "QRcheckScene.h"
#include "MainSelectScene.h"
#include "zarBarViewController.h"
#include "AppController.h"

USING_NS_CC;

Scene* QRcheck::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = QRcheck::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool QRcheck::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //二维码识别的viewcontroller
    zarBarViewController *testvc = [[zarBarViewController alloc] init];
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    [appController.viewController presentModalViewController:testvc animated:YES];
    

    
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
    auto backItem = MenuItemImage::create("navbackbg.png","navbackbg.png",CC_CALLBACK_1(QRcheck::gotoBack, this));
	backItem->setPosition(cocos2d::Point(origin.x+50, origin.y + visibleSize.height - label->getContentSize().height));
    auto backmenu = Menu::create(backItem, NULL);
    backmenu->setPosition(cocos2d::Point::ZERO);
    this->addChild(backmenu);

    return true;
}

void QRcheck::gotoBack(Object* pSender){
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.3, MainSelect::createScene()));
}



