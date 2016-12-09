
#ifndef TestCpp_PopupLayer_h
#define TestCpp_PopupLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class PopupLayer: public Layer{
public:
    
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    CREATE_FUNC(PopupLayer);
};

#endif