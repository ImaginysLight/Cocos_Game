/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <network\SocketIO.h>
#include "ui\CocosGUI.h"
#include <iostream>


using namespace cocos2d::network;
using namespace cocos2d;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
    auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Client = network::SocketIO::getInstance()->connect("http://192.168.114.1:3000", *this);//connect sever

	

	///////////////////////////////////////////////////////
	Text_Field = TextField::create("...","fonts/Marker Felt.ttf", 20);
	Text_Field->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.8f));

	Text_Field->setText("Anh Quyet");
	Client->emit("hello", "[{\"value\":\"" + Text_Field->getStringValue() + "\"}]");

	Text_Field->addEventListener([](Ref* node, ui::TextField::EventType event)
	{


		//TextField * text = TextField::;
		//std::string send_text = "";
		//// do stuff in here with event
		//if (event == ui::TextField::EventType::DETACH_WITH_IME)
		//{
		//	send_text = "[{\"value\":\"" + Text_Field->getStringValue() + "\"}]";
		//	Client->emit("hello", send_text);
		//	//Client->send("hello");
		//	//Client->disconnect();
		//}
	}
	);

	this->addChild(Text_Field);
	//////////////////////////////////////////////////////////////////////////////
	


    //connect to server
    // i don't know what is meant be *delegate ? is that *this or something else, anyone ?
    //network::SIOClient *client = network::SocketIO::connect(*delegate, "ws://localhost:3000");

    // how to detect error could not connect ?

    //send message
   

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//void HelloWorld::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
//{
//	if (200 != response->getResponseCode())
//	{
//		printf("Succeeded");
//
//		return;
//	}
//	else
//	{
//		printf("Failed");
//	}
//}


void HelloWorld::TextFileEvent(cocos2d::Ref * sender, TextField::EventType type)
{
	TextField * text;
	std::string send_text;
	switch (type)
	{
	case TextField::EventType::DETACH_WITH_IME:
			text = (TextField*)sender;
			send_text = "[{\"value\":\"" + text->getStringValue() + "\"}]";
			Client->emit("hello", send_text);
            Client->send("hello");
            Client->disconnect();
			break;
	default:
		break;
	}
}


void HelloWorld::onReceiveEvent(network::SIOClient *client, const std::string &data)
{
	CCLOG("ON RECIEVE");
	CCLOG("ON RECIEVE: %s", data.c_str());
}

void HelloWorld::onConnect(SIOClient* client){}
void HelloWorld::onMessage(SIOClient* client, const std::string &data) {}
void HelloWorld::onClose(SIOClient* client) {}
void HelloWorld::onError(SIOClient* client, const std::string &data) {}
