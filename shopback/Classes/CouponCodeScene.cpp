
#include "CouponCodeScene.h"
#include "MainSelectScene.h"
#include "CouponDetailScene.h"
#include "jsoncpp/include/json/json.h"

using namespace cocos2d::network;

USING_NS_CC;

Scene* CouponCode::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CouponCode::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CouponCode::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //大背景图片
    auto sprite = Sprite::create("background.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite);
    
    //顶部navigationbar图
    auto spritebar = Sprite::create("head.png");
    spritebar->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height + origin.y - spritebar->getContentSize().height/2));
    this->addChild(spritebar);
    
    //顶部navigationbar标题文本
    auto label = LabelTTF::create("容易逛商家后台", "Arial", 40);
    label->setPosition(Point(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label);
    
    //顶部navigationbar返回按钮
    auto backItem = MenuItemImage::create("navbackbg.png","navbackbg.png",CC_CALLBACK_1(CouponCode::gotoBack, this));
	backItem->setPosition(Point(origin.x+50, origin.y + visibleSize.height - label->getContentSize().height));
    auto backmenu = Menu::create(backItem, NULL);
    backmenu->setPosition(Point::ZERO);
    this->addChild(backmenu);

    
    //---------------------------------------------------------------------
    
    
    Size childsSize = Size(233*2, 33*2);
    float childsDis = 50.0;
    int childsNum = 2;
    float childsWholeHeight = childsSize.height * childsNum + childsDis * (childsNum - 1);
    
    textinputpw = EditBox::create(childsSize, Scale9Sprite::create("inputbg.png"));
    textinputpw->cocos2d::CCNode::setPosition(Point(visibleSize.width * 0.5, (visibleSize.height - childsWholeHeight + childsSize.height)*0.5 + (childsSize.height + childsDis) * 1));
    textinputpw->setFontSize(20);
    textinputpw->setFontColor(Color3B(0,0,0));
    textinputpw->setPlaceHolder("请输入优惠码");
    this->addChild(textinputpw);
    
    auto btnselectimg1 = Scale9Sprite::create("btn1_big.png");
    auto btnnomarlimg1 = Scale9Sprite::create("btn2_big.png");
    auto label1 = LabelTTF::create("核销", "Marker Felt", 35);
    auto btn1 = ControlButton::create(label1, btnnomarlimg1);
    btn1->setPreferredSize(childsSize);
    btn1->setZoomOnTouchDown(false);
    btn1->setPosition(Point(visibleSize.width * 0.5, (visibleSize.height - childsWholeHeight + childsSize.height)*0.5 + (childsSize.height + childsDis) * 0));
    btn1->setBackgroundSpriteForState(btnselectimg1, Control::State::HIGH_LIGHTED);
    btn1->setTitleColorForState(Color3B(255, 255, 255), Control::State::HIGH_LIGHTED);
    btn1->addTargetWithActionForControlEvents(this, cccontrol_selector(CouponCode::gotoShowCoupons), Control::EventType::TOUCH_DOWN);
    this->addChild(btn1);


    return true;
}

void CouponCode::gotoShowCoupons(Object* pSender, Control::EventType controlEvent){
    CCLOG("Touch the Button");
    auto request = new HttpRequest();
    std::string urlstr = "http://test.rongyi.com/api/shop_app_v1/redeem_line_items/";
    urlstr = urlstr + textinputpw->getText()+"?token="+"tokenvalue";
    request->setUrl(urlstr.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    std::vector<std::string> header;
    header.push_back("application/vnd.rongyi.v3");
    request->setHeaders(header);
    request->setResponseCallback(this, httpresponse_selector(CouponCode::onHttpRequestCompleted));
    network::HttpClient::getInstance()->send(request);
}
void CouponCode::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    std::vector<char>* buffer = response->getResponseData();
    CCLOG("Http Test, dump data: ");
    
    //转化为str类型
    std::string str;
    str.insert(str.begin(), buffer->begin(), buffer->end());
    std::cout<<"str: "<<str;
    
    Json::Value parsedata;
    Json::Reader reader;
    reader.parse(str, parsedata);
    //Json::Value parseArray = parsedata.get("meta", parseArray);
    //CCLOG("sadfsdfsdfaaaaaaarrrrr %d",parseArray.size());
    
    Scene* scene = CCScene::create();
    CouponDetail *layer = CouponDetail::create();
    //layer->couponcode = couponinfo;
    layer->getUseCouponData();
    scene->addChild(layer);
    Director::getInstance()->pushScene(TransitionSlideInR::create(0.3, scene));
}

void CouponCode::gotoBack(Object* pSender){
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.3, MainSelect::createScene()));
}



