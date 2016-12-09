#ifndef ShowCoupons_SCENE_H__
#define ShowCoupons_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "jsoncpp/include/json/json.h"

USING_NS_CC;
USING_NS_CC_EXT;

struct CouponInfo{
    std::string couponid;
    std::string title;
    std::string discrib;
    int salenum;
    int usednum;
    int resalenum;
    std::string usedata;
};

class ShowCoupons : public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void gotoBack(Object* pSender);
    
    TableView *tableView;
    Json::Value parseArray;
    
    //TableViewDataSource
//    virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx);
//    virtual cocos2d::Size cellSizeForTable(TableView *table);
//    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
//    virtual ssize_t numberOfCellsInTableView(TableView *table);
//    
//    //TableViewDelegate
//    virtual void scrollViewDidScroll(ScrollView* view);
//    virtual void scrollViewDidZoom(ScrollView* view);
//    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
//    virtual void tableCellHighlight(TableView* table, TableViewCell* cell);
//    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell);
//    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell);
    
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    virtual void onHttpRequestCompleted(cocos2d::network::HttpClient* sender,
                                        cocos2d::network::HttpResponse* response);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ShowCoupons);
};

#endif // __HELLOWORLD_SCENE_H__
