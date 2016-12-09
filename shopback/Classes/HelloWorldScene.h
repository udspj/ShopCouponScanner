#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"

USING_NS_CC_EXT;

class HelloWorld : public cocos2d::Layer

{
    
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void loginNamePassword(Object * sender, Control::EventType controlEvent);
    CREATE_FUNC(HelloWorld);
    virtual void onHttpRequestCompleted(cocos2d::network::HttpClient* sender,
                                        cocos2d::network::HttpResponse* response);
    
    EditBox *textinputname;
    EditBox *textinputpw;
};

#endif // __HELLOWORLD_SCENE_H__
