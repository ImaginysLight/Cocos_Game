#ifndef __NETWORK_Server_Listen_SCENE_H__
#define __NETWORK_Server_Listen_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"

class Server_Listen : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Server_Listen);
    
    void onHttpRequestCompleted( cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response );
};

#endif // __NETWORK_Server_Listen_SCENE_H__