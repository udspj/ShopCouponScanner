#ifndef CouponDetail_SCENE_H__
#define CouponDetail_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ShowCouponsScene.h"
#include "network/HttpClient.h"

USING_NS_CC_EXT;

class CouponDetail : public cocos2d::LayerColor
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    CouponInfo couponcode;
    
    // a selector callback
    void gotoUseCoupons(Object* pSender, Control::EventType controlEvent);
    void gotoBackCoupons(Object* pSender, Control::EventType controlEvent);
    
    void gotoBack(Object* pSender);
    
    void getShowCouponData();
    void getUseCouponData();
    virtual void onHttpRequestCompleted(cocos2d::network::HttpClient* sender,
                                        cocos2d::network::HttpResponse* response);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CouponDetail);
};

#endif // __HELLOWORLD_SCENE_H__
