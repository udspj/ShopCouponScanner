#ifndef CouponCode_SCENE_H__
#define CouponCode_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"

USING_NS_CC_EXT;

class CouponCode : public cocos2d::Layer
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    EditBox *textinputpw;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void gotoShowCoupons(Object* pSender, Control::EventType controlEvent);
    void gotoBack(Object* pSender);
    virtual void onHttpRequestCompleted(cocos2d::network::HttpClient* sender,
                                        cocos2d::network::HttpResponse* response);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CouponCode);
};

#endif // __HELLOWORLD_SCENE_H__
