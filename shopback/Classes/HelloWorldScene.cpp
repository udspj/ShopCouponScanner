#include "HelloWorldScene.h"
#include "MainSelectScene.h"
#include "jsoncpp/include/json/json.h"

using namespace cocos2d::network;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
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
    
    
    //---------------------------------------------------------------------
    
    Size childsSize = Size(233*2, 33*2);
    float childsDis = 50.0;
    int childsNum = 3;
    float childsWholeHeight = childsSize.height * childsNum + childsDis * (childsNum - 1);
    
    //第一个size参数表示输入编辑框的大小，第二个参数九宫格是用于输入编辑框的背景
    textinputname = EditBox::create(childsSize, Scale9Sprite::create("inputbg.png"));
    textinputname->cocos2d::CCNode::setPosition(Point(visibleSize.width * 0.5, (visibleSize.height - childsWholeHeight + childsSize.height)*0.5 + (childsSize.height + childsDis) * 2));
    //以setFont开头的有几个方法是 用于设置输入文字的字体，大小，颜色
    textinputname->setFontSize(20);
    textinputname->setFontColor(Color3B(0,0,0));
    //设置输入编辑框在还没有输入的时候默认的提示文字
    textinputname->setPlaceHolder("请输入您的用户名");
    //同样的，也有几个对应的方法的是用于设置这些提示文字的，都是以setPlaceHolder开头的
    //editBox->setPlaceholderFontColor(ccWHITE);
    this->addChild(textinputname);
    
    textinputpw = EditBox::create(childsSize, Scale9Sprite::create("inputbg.png"));
    textinputpw->cocos2d::CCNode::setPosition(Point(visibleSize.width * 0.5, (visibleSize.height - childsWholeHeight + childsSize.height)*0.5 + (childsSize.height + childsDis) * 1));
    textinputpw->setFontSize(20);
    textinputpw->setFontColor(Color3B(0,0,0));
    textinputpw->setPlaceHolder("请输入您的密码");
    this->addChild(textinputpw);
    
    auto btnselectimg = Scale9Sprite::create("btn1_big.png");
    auto btnnomarlimg = Scale9Sprite::create("btn2_big.png");
    auto loginlabel = LabelTTF::create("登录", "Marker Felt", 35);
    auto loginbtn = ControlButton::create(loginlabel, btnnomarlimg);
    loginbtn->setPreferredSize(childsSize);
    loginbtn->setZoomOnTouchDown(false);
    loginbtn->setPosition(Point(visibleSize.width * 0.5, (visibleSize.height - childsWholeHeight + childsSize.height)*0.5 + (childsSize.height + childsDis) * 0));
    loginbtn->setBackgroundSpriteForState(btnselectimg, Control::State::HIGH_LIGHTED);
    loginbtn->setTitleColorForState(Color3B(255, 255, 255), Control::State::HIGH_LIGHTED);
    loginbtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::loginNamePassword), Control::EventType::TOUCH_UP_INSIDE);
    this->addChild(loginbtn);
    
    
    return true;
}

void HelloWorld::loginNamePassword(Object * sender, Control::EventType controlEvent){
    CCLOG("Touch the Button");
    Director::getInstance()->replaceScene(TransitionSlideInR::create(0.3, MainSelect::createScene()));
    //Director::getInstance()->replaceScene(TransitionSlideInR::create(0.3, CouponDetail::createScene()));
    
//    auto request = new HttpRequest();
//    request->setUrl("http://test.rongyi.com/api/shop_app_v1/sessions");
//    request->setRequestType(HttpRequest::Type::POST);
//    std::vector<std::string> header;
//    header.push_back("application/vnd.rongyi.v3");
//    request->setHeaders(header);
//    request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));
//    const char* postData = "id=defaultname;password=123456";
//    request->setRequestData(postData, strlen(postData));
//    network::HttpClient::getInstance()->send(request);
}

void HelloWorld::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
    std::vector<char>* buffer = response->getResponseData();
    CCLOG("Http Test, dump data: ");
    
    //转化为str类型
    std::string str;
    str.insert(str.begin(), buffer->begin(), buffer->end());
    std::cout<<"str: "<<str;
    
    //jsoncpp.sourceforge.net/
    
    Json::Value parsedata;
    Json::Reader reader;
    reader.parse(str, parsedata);
    //Json::Value parseArray = parsedata.get("meta", parseArray);
    //CCLOG("sadfsdfsdfaaaaaaarrrrr %d",parseArray.size());
    
    std::cout<<"parseArray: "<<parsedata["meta"]["status"].asInt();
    int status = parsedata["meta"]["status"].asInt();
    if (status == 1) {
        CCLOG("name password error!!");
        Director::getInstance()->replaceScene(TransitionSlideInR::create(0.3, MainSelect::createScene()));
    }else{
        Director::getInstance()->replaceScene(TransitionSlideInR::create(0.3, MainSelect::createScene()));
    }
    
    
//    for ( int index = 0; index < parseArray.size(); ++index ){
//        parseArray[index]["name"].asString();
//        std::cout<<"parseArray: "<<parseArray[index]["name"].asString();
//    }
    
//    std::string nameStr =parseArray[0]["name"] ;
//    CCLOG("name:%s",nameStr);
}

//单例token
//网络请求loading
//popsence切换动画
//自定义tableviewcell
//pop返回按钮状态还处在按下状态
//无网络下coupon列表闪退

//自定义layer做alert
//blog.csdn.net/onerain88/article/details/7608496
//www.ityran.com/archives/4854

//cocos2dx和oc混编
//www.himigame.com/iphone-cocos2dx/743.html sprite混用
//game center
//d.hatena.ne.jp/okahiro_p/20130311/1363007151

//在UIKit中使用cocos2d-x
//www.ityran.com/archives/2028



