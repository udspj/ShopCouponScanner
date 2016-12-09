
#include "ShowCouponsScene.h"
#include "MainSelectScene.h"
#include "CustomTableViewCell.h"
#include "CouponDetailScene.h"
#include <vector>

using namespace cocos2d::network;
using namespace cocos2d;

USING_NS_CC;
USING_NS_CC_EXT;

Scene* ShowCoupons::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ShowCoupons::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShowCoupons::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //大背景图片
//    auto sprite = Sprite::create("background.png");
//    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(sprite);
    
    //顶部navigationbar图
    auto spritebar = Sprite::create("head.png");
    spritebar->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height + origin.y - spritebar->getContentSize().height/2));
    this->addChild(spritebar);
    
    //顶部navigationbar标题文本
    auto label = LabelTTF::create("容易逛商家后台", "Arial", 40);
    label->setPosition(Point(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label);
    
    //顶部navigationbar返回按钮
    auto backItem = MenuItemImage::create("navbackbg.png","navbackbg.png",CC_CALLBACK_1(ShowCoupons::gotoBack, this));
	backItem->setPosition(Point(origin.x+50, origin.y + visibleSize.height - label->getContentSize().height));
    auto backmenu = Menu::create(backItem, NULL);
    backmenu->setPosition(Point::ZERO);
    this->addChild(backmenu);

    
    //---------------------------------------------------------------------
    
    
	tableView = TableView::create(this, Size(visibleSize.width, visibleSize.height-88));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(Point(0,0));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
    
    auto request = new HttpRequest();
    request->setUrl("http://test.rongyi.com/webapi/phone/switch/coupons.htm?coordX=121.431892&coordY=31.194862&cityName=上海市&pageNum=1&zone_id=all&categoryCode=all&orderType=default&sign=6c55dc15a580537d4542604cfa04c1aa");
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(ShowCoupons::onHttpRequestCompleted));
    network::HttpClient::getInstance()->send(request);
    
//以后再增加上头两个筛选按钮

    return true;
}

void ShowCoupons::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
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
    parseArray = parsedata.get("dataList", NULL);
    
	tableView->reloadData();
}


ssize_t ShowCoupons::numberOfCellsInTableView(TableView *table)
{
    return 20;
}

Size ShowCoupons::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(320, 200);
}

TableViewCell* ShowCoupons::tableCellAtIndex(TableView *table, ssize_t idx)
{
    std::cout<<"parseArray: "<<parseArray[idx]["name"].asString();
    
    auto title = String::createWithFormat("%s", parseArray[idx]["title"].asString().c_str());
    auto salenum = String::createWithFormat("已售出数量：%d", parseArray[idx]["activityCount"].asInt());
    auto usednum = String::createWithFormat("已核销数量：%d", parseArray[idx]["juanCount"].asInt());
    auto usedata = String::createWithFormat("有效期至：%s", parseArray[idx]["endTime"].asString().c_str());
    
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        auto sprite = Sprite::create("cell_bk.png");
        sprite->setAnchorPoint(Point::ZERO);
        sprite->setPosition(Point::ZERO);
        cell->addChild(sprite);
        
        auto labeltitle = LabelTTF::create(title->getCString(), "Helvetica", 30.0);
        labeltitle->setColor(Color3B(0, 0, 0));
        labeltitle->setPosition(Point(20, 150));
		labeltitle->setAnchorPoint(Point::ZERO);
        labeltitle->setTag(101);
        cell->addChild(labeltitle);
        
        auto labelsale = LabelTTF::create(salenum->getCString(), "Helvetica", 20.0);
        labelsale->setColor(Color3B(0, 0, 0));
        labelsale->setPosition(Point(20, 100));
		labelsale->setAnchorPoint(Point::ZERO);
        labelsale->setTag(102);
        cell->addChild(labelsale);
        
        auto labelused = LabelTTF::create(usednum->getCString(), "Helvetica", 20.0);
        labelused->setColor(Color3B(0, 0, 0));
        labelused->setPosition(Point(20, 60));
		labelused->setAnchorPoint(Point::ZERO);
        labelused->setTag(103);
        cell->addChild(labelused);
        
        auto labeldata = LabelTTF::create(usedata->getCString(), "Helvetica", 20.0);
        labeldata->setColor(Color3B(0, 0, 0));
        labeldata->setPosition(Point(20, 20));
		labeldata->setAnchorPoint(Point::ZERO);
        labeldata->setTag(104);
        cell->addChild(labeldata);
    }else{
        auto labeltitle = (LabelTTF*)cell->getChildByTag(101);
        labeltitle->setString(title->getCString());
        auto labelsale = (LabelTTF*)cell->getChildByTag(102);
        labelsale->setString(salenum->getCString());
        auto labelused = (LabelTTF*)cell->getChildByTag(103);
        labelused->setString(usednum->getCString());
        auto labeldata = (LabelTTF*)cell->getChildByTag(104);
        labeldata->setString(usedata->getCString());
    }
    
    return cell;
}

void ShowCoupons::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %ld", cell->getIdx());
    Scene* scene = CCScene::create();
    CouponDetail *layer = CouponDetail::create();
    
    ssize_t idx = cell->getIdx();
    
    //std::vector<CouponInfo> valueDic;
    CouponInfo couponinfo;
    couponinfo.title = parseArray[idx]["title"].asString().c_str();
    couponinfo.couponid = parseArray[idx]["code"].asString().c_str();
    couponinfo.discrib = parseArray[idx]["name"].asString().c_str();
    couponinfo.salenum = parseArray[idx]["activityCount"].asInt();
    couponinfo.usednum = parseArray[idx]["juanCount"].asInt();
    couponinfo.resalenum = parseArray[idx]["juanCount"].asInt();
    couponinfo.usedata = parseArray[idx]["endTime"].asString().c_str();
    //valueDic.push_back(couponinfo);
    
//    CCDictionary* couponDic = CCDictionary::create();
//    CCString* pValue1 = CCString::create(parseArray[idx]["title"].asString().c_str());
//    CCString* pValue2 = CCString::create(parseArray[idx]["code"].asString().c_str());
//    CCString* pValue3 = CCString::create(parseArray[idx]["name"].asString().c_str());
//    CCInteger* pValue4 = CCInteger::create(parseArray[idx]["activityCount"].asInt());
//    CCInteger* pValue5 = CCInteger::create(parseArray[idx]["juanCount"].asInt());
//    CCInteger* pValue6 = CCInteger::create(parseArray[idx]["juanCount"].asInt());
//    CCString* pValue7 = CCString::create(parseArray[idx]["endTime"].asString().c_str());
//    couponDic->setObject(pValue1, "title");
//    couponDic->setObject(pValue2, "id");
//    couponDic->setObject(pValue3, "name");
//    couponDic->setObject(pValue4, "activityCount");
//    couponDic->setObject(pValue5, "juanCount");
//    couponDic->setObject(pValue6, "juanCount");
//    couponDic->setObject(pValue7, "endTime");
    
    layer->couponcode = couponinfo;
    layer->getShowCouponData();
    scene->addChild(layer);
    //CCLOG("sssssscouponcode  %s",layer->couponcode.c_str());
    Director::getInstance()->pushScene(TransitionSlideInR::create(0.3, scene));
    
//    CouponDetail->couponcode = "00000";//blog.csdn.net/cwn0812/article/details/8792968
//    Scene* scene = CouponDetail::create();
//    CCLOG("sssssscouponcode  %s",layer->couponcode.c_str());
    //Director::getInstance()->pushScene(TransitionSlideInR::create(0.3, CouponDetail::createScene()));
}



void ShowCoupons::gotoBack(Object* pSender){
    Director::getInstance()->replaceScene(TransitionSlideInL::create(0.3, MainSelect::createScene()));
}



