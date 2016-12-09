
#include "CouponDetailScene.h"
#include "jsoncpp/include/json/json.h"

using namespace cocos2d::network;

USING_NS_CC;


Scene* CouponDetail::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CouponDetail::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CouponDetail::init()
{
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //大背景图片
    
    //顶部navigationbar图
    auto spritebar = Sprite::create("head.png");
    spritebar->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height + origin.y - spritebar->getContentSize().height/2));
    this->addChild(spritebar);
    
    //顶部navigationbar标题文本
    auto label = LabelTTF::create("容易逛商家后台", "Arial", 40);
    label->setPosition(Point(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label);
    
    //顶部navigationbar返回按钮
    auto backItem = MenuItemImage::create("navbackbg.png","navbackbg.png",CC_CALLBACK_1(CouponDetail::gotoBack, this));
	backItem->setPosition(Point(origin.x+50, origin.y + visibleSize.height - label->getContentSize().height));
    auto backmenu = Menu::create(backItem, NULL);
    backmenu->setPosition(Point::ZERO);
    this->addChild(backmenu);

    
    //---------------------------------------------------------------------
    
    


    //CCLOG("couponcode  %s",couponcode.c_str());
    

    return true;
}

void CouponDetail::getShowCouponData(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Size childsSize = Size(108*2, 33*2);
    float childsDis = 80.0;
    int childsNum = 2;
    float childsWholeWidth = childsSize.width * childsNum + childsDis * (childsNum - 1);
    
    //标题
    auto labeltitle = LabelTTF::create(couponcode.title, "Helvetica", 30.0);
    labeltitle->setColor(Color3B(0, 0, 0));
    labeltitle->setPosition(Point(20, visibleSize.height-88-50));
    labeltitle->setAnchorPoint(Point::ZERO);
    labeltitle->setTag(101);
    this->addChild(labeltitle);
    
    //说明
    auto labeldiscrib = LabelTTF::create(couponcode.discrib, "Helvetica", 25, Size(visibleSize.width-40,200),TextHAlignment::LEFT,TextVAlignment::TOP);
    labeldiscrib->setColor(Color3B(0, 0, 0));
    labeldiscrib->setPosition(Point(20, visibleSize.height-88-260));
    labeldiscrib->setAnchorPoint(Point::ZERO);
    labeldiscrib->setTag(102);
    this->addChild(labeldiscrib);
    
    //解释权
    auto labelps = LabelTTF::create("更多详情请咨询商家，具体优惠内容，以店铺实际为准", "Helvetica", 20.0);
    labelps->setColor(Color3B(0, 0, 0));
    labelps->setPosition(Point(20, visibleSize.height-88-300));
    labelps->setAnchorPoint(Point::ZERO);
    labelps->setTag(103);
    this->addChild(labelps);
    
    
    
    //分割线-----------------------------
    auto sprite = Sprite::create("line.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height-88-320));
    this->addChild(sprite);
    
    auto salenum = String::createWithFormat("已售出数量：%d张", couponcode.salenum);
    auto usednum = String::createWithFormat("已核销数量：%d张", couponcode.usednum);
    auto resalenum = String::createWithFormat("退款数量：%d张", couponcode.resalenum);
    auto usedata = String::createWithFormat("有效期至：%s", couponcode.usedata.c_str());
    
    //已售出数量
    auto labelsale = LabelTTF::create(salenum->getCString(), "Helvetica", 25.0);
    labelsale->setColor(Color3B(0, 0, 0));
    labelsale->setPosition(Point(20, visibleSize.height-88-380));
    labelsale->setAnchorPoint(Point::ZERO);
    labelsale->setTag(102);
    this->addChild(labelsale);
    
    //核销数量
    auto labelused = LabelTTF::create(usednum->getCString(), "Helvetica", 25.0);
    labelused->setColor(Color3B(0, 0, 0));
    labelused->setPosition(Point(20, visibleSize.height-88-430));
    labelused->setAnchorPoint(Point::ZERO);
    labelused->setTag(103);
    this->addChild(labelused);
    
    //退款数
    auto labelresale = LabelTTF::create(resalenum->getCString(), "Helvetica", 25.0);
    labelresale->setColor(Color3B(0, 0, 0));
    labelresale->setPosition(Point(20, visibleSize.height-88-480));
    labelresale->setAnchorPoint(Point::ZERO);
    labelresale->setTag(104);
    this->addChild(labelresale);
    
    //有效期至
    auto labeldata = LabelTTF::create(usedata->getCString(), "Helvetica", 25.0);
    labeldata->setColor(Color3B(0, 0, 0));
    labeldata->setPosition(Point(20, visibleSize.height-88-530));
    labeldata->setAnchorPoint(Point::ZERO);
    labeldata->setTag(104);
    this->addChild(labeldata);
}
void CouponDetail::getUseCouponData(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Size childsSize = Size(108*2, 33*2);
    float childsDis = 80.0;
    int childsNum = 2;
    float childsWholeWidth = childsSize.width * childsNum + childsDis * (childsNum - 1);
    
    //标题
    auto labeltitle = LabelTTF::create("优惠券1", "Helvetica", 30.0);//couponcode.title
    labeltitle->setColor(Color3B(0, 0, 0));
    labeltitle->setPosition(Point(20, visibleSize.height-88-50));
    labeltitle->setAnchorPoint(Point::ZERO);
    labeltitle->setTag(101);
    this->addChild(labeltitle);
    
    //说明
    auto labeldiscrib = LabelTTF::create("优惠券1111111111111", "Helvetica", 25, Size(visibleSize.width-40,200),TextHAlignment::LEFT,TextVAlignment::TOP);//couponcode.discrib
    labeldiscrib->setColor(Color3B(0, 0, 0));
    labeldiscrib->setPosition(Point(20, visibleSize.height-88-260));
    labeldiscrib->setAnchorPoint(Point::ZERO);
    labeldiscrib->setTag(102);
    this->addChild(labeldiscrib);
    
    //解释权
    auto labelps = LabelTTF::create("更多详情请咨询商家，具体优惠内容，以店铺实际为准", "Helvetica", 20.0);
    labelps->setColor(Color3B(0, 0, 0));
    labelps->setPosition(Point(20, visibleSize.height-88-300));
    labelps->setAnchorPoint(Point::ZERO);
    labelps->setTag(103);
    this->addChild(labelps);
    
    
    
    //分割线-----------------------------
    auto sprite = Sprite::create("line.png");
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height-88-320));
    this->addChild(sprite);
    
    auto usedata = String::createWithFormat("有效期至：%s","2014-12-31"); //couponcode.usedata.c_str());
    auto usestatus = String::createWithFormat("核销状态：%s","未核销");
    
    //有效期至
    auto labeldata = LabelTTF::create(usedata->getCString(), "Helvetica", 25.0);
    labeldata->setColor(Color3B(0, 0, 0));
    labeldata->setPosition(Point(20, visibleSize.height-88-380));
    labeldata->setAnchorPoint(Point::ZERO);
    labeldata->setTag(104);
    this->addChild(labeldata);
    
    //核销状态
    auto labelstatus = LabelTTF::create(usestatus->getCString(), "Helvetica", 25.0);
    labelstatus->setColor(Color3B(0, 0, 0));
    labelstatus->setPosition(Point(20, visibleSize.height-88-430));
    labelstatus->setAnchorPoint(Point::ZERO);
    labelstatus->setTag(104);
    this->addChild(labelstatus);
    
    
    //“确认” “返回” 按钮-----------------------
    
    auto btnselectimg1 = Scale9Sprite::create("btn1_small.png");
    auto btnnomarlimg1 = Scale9Sprite::create("btn2_small.png");
    auto label1 = LabelTTF::create("确认核销", "Marker Felt", 35);
    auto btn1 = ControlButton::create(label1, btnnomarlimg1);
    btn1->setPreferredSize(childsSize);
    btn1->setZoomOnTouchDown(false);
    btn1->setPosition(Point((visibleSize.width - childsWholeWidth + childsSize.width)*0.5 + (childsSize.width + childsDis) * 0,visibleSize.height-88-500));
    btn1->setBackgroundSpriteForState(btnselectimg1, Control::State::HIGH_LIGHTED);
    btn1->setTitleColorForState(Color3B(255, 255, 255), Control::State::HIGH_LIGHTED);
    btn1->addTargetWithActionForControlEvents(this, cccontrol_selector(CouponDetail::gotoUseCoupons), Control::EventType::TOUCH_DOWN);
    this->addChild(btn1);
    
    auto btnselectimg2 = Scale9Sprite::create("btn1_small.png");
    auto btnnomarlimg2 = Scale9Sprite::create("btn2_small.png");
    auto label2 = LabelTTF::create("返回", "Marker Felt", 35);
    auto btn2 = ControlButton::create(label2, btnnomarlimg2);
    btn2->setPreferredSize(childsSize);
    btn2->setZoomOnTouchDown(false);
    btn2->setPosition(Point((visibleSize.width - childsWholeWidth + childsSize.width)*0.5 + (childsSize.width + childsDis) * 1,visibleSize.height-88-500));
    btn2->setBackgroundSpriteForState(btnselectimg2, Control::State::HIGH_LIGHTED);
    btn2->setTitleColorForState(Color3B(255, 255, 255), Control::State::HIGH_LIGHTED);
    btn2->addTargetWithActionForControlEvents(this, cccontrol_selector(CouponDetail::gotoBackCoupons), Control::EventType::TOUCH_DOWN);
    this->addChild(btn2);
}


void CouponDetail::gotoUseCoupons(Object* pSender, Control::EventType controlEvent){
    auto request = new HttpRequest();
    request->setUrl("http://test.rongyi.com/api/shop_app_v1/exchanges/completed");
    request->setRequestType(HttpRequest::Type::POST);
    std::vector<std::string> header;
    header.push_back("application/vnd.rongyi.v3");
    request->setHeaders(header);
    request->setResponseCallback(this, httpresponse_selector(CouponDetail::onHttpRequestCompleted));
    const char* postData = "uuid=defaultname;token=123456;type=123456";
    request->setRequestData(postData, strlen(postData));
    network::HttpClient::getInstance()->send(request);
}
void CouponDetail::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    
    //核销失败弹出alert
    MessageBox("核销失败\n请重试", "");
}

void CouponDetail::gotoBackCoupons(Object* pSender, Control::EventType controlEvent){
    Director::getInstance()->popScene();
}

void CouponDetail::gotoBack(Object* pSender){
    Director::getInstance()->popScene();
}



