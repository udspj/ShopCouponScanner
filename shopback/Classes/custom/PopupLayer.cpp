//
// PopupLayer.cpp
// TestCpp
//
// Created by leafsoar on 7/29/13.
//
//

#include "PopupLayer.h"

bool PopupLayer::init(){
    bool bRef = false;
    do{
        CC_BREAK_IF(!CCLayer::init());
        
        bRef = true;
    }while(0);
    return bRef;
}


void PopupLayer::onEnter(){
    CCLayer::onEnter();
    
}

void PopupLayer::onExit(){
    CCLayer::onExit();
}

