#include "ClientScene.h"
#include <vector>
#include "ui\CocosGUI.h"

using namespace cocos2d::ui;

USING_NS_CC;

using namespace std;

// ANDROID requires
// <uses-permission android:name="android.permission.INTERNET"/>

// DON'T Forget to add "App Transport Security Settings" to Info.plist
// DON'T Forget to add "Allow Arbitrary Loads" under the previous section added inside of Info.plist and set it to YES

Scene* Client::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Client::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Client::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Text_Field = TextField::create("...", "fonts/Marker arial.ttf", 40);
	Text_Field->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.8f));
	this->addChild(Text_Field);
	
	Text_Field->addEventListener(CC_CALLBACK_2(Client::TextFieldEvent, this));



	/*__String *data_To_Send = __String::create("dataOne=&dataTwo=35");
	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setUrl("http://localhost:7331/Project_Test/Post.php");
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setRequestData(data_To_Send->getCString(), data_To_Send->length());
	request->setResponseCallback(CC_CALLBACK_2(Client::onHttpRequestCompleted, this));
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();*/

	

    return true;
}

void Client::onHttpRequestCompleted( cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response )
{    
	string a = "";
	auto result = TextField::create("...", "fonts/Marker arial.ttf", 40);
	result->setPosition(Vec2(500, 500));
	std:vector<char> *buffer = response->getResponseData();
	CCLOG("get data from sever: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		//CCLOG("%c",(*buffer)[i]);
		a = a + (*buffer)[i];
	}
	CCLOG("%s", a);
	result->setText(a);
	this->addChild(result);
	printf("Response Code: %li\n", response->getResponseCode());

    if ( 200 == response->getResponseCode( ) )
    {
		CCLOG( "Succeeded" );
    }
    else
    {
		CCLOG( "Failed" );
    }
}

void Client::TextFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type) {
	TextField * text;
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
		break;
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
	{
		text = (TextField*)pSender;
		Client::content = text->getString();
		CCLOG("%s", Client::content.c_str());
		__String *data_To_Send = __String::create("dataOne="+ Client::content);
		cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
		request->setUrl("http://localhost:7331/Project_Test/Post.php");
		request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
		request->setRequestData(data_To_Send->getCString(), data_To_Send->length());
		request->setResponseCallback(CC_CALLBACK_2(Client::onHttpRequestCompleted, this));
		cocos2d::network::HttpClient::getInstance()->send(request);
		request->release();
		break;
	}
	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
		break;
	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
		break;
	default:
		break;
	}
}

