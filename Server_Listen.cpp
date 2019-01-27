#include "Server_Listen.h"
#include <vector>

USING_NS_CC;

using namespace std;

// ANDROID requires
// <uses-permission android:name="android.permission.INTERNET"/>

// DON'T Forget to add "App Transport Security Settings" to Info.plist
// DON'T Forget to add "Allow Arbitrary Loads" under the previous section added inside of Info.plist and set it to YES

Scene* Server_Listen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Server_Listen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Server_Listen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
	request->setUrl("http://localhost:7331/Project_Test/Post.php");
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	std::vector<std::string> headers;
	headers.push_back("Content-Type: application/json; charset=utf-8");
	request->setHeaders(headers);
	request->setResponseCallback(CC_CALLBACK_2(Server_Listen::onHttpRequestCompleted, this));

	// write the post data

	std::string postData = "id=mihir&pass=thkr";
	request->setRequestData(postData.c_str(), postData.length());
	request->setTag("POST test2");
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
    
    return true;
}

void Server_Listen::onHttpRequestCompleted( cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response )
{    
	/*std:vector<char> *buffer = response->getResponseData();
	CCLOG("get data from sever: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		CCLOG("%c", (*buffer)[i]);
	}*/
	
	CCLOG("Response Code: %li\n", response->getResponseCode());

    if ( 200 == response->getResponseCode( ) )
    {
		CCLOG( "Succeeded" );
    }
    else
    {
		CCLOG( "Failed" );
    }
}