#ifndef __NETWORK_CLIENT_SCENE_H__
#define __NETWORK_CLIENT_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "ui\CocosGUI.h"

using namespace cocos2d::ui;

class Client : public cocos2d::Layer
{
private: 

	TextField *Text_Field;
	std::string content;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Client);
	void TextFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);
    void onHttpRequestCompleted( cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response );
};

#endif // __NETWORK_CLIENT_SCENE_H__