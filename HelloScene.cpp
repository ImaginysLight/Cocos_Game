#include "HelloScene.h"
#include "PlayerCode.h"
#include <fstream>
#include "ui/CocosGUI.h"


USING_NS_CC;
using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;
Scene* Hello::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Hello::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Hello::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Label
	auto labelQuestion = Label::createWithSystemFont("Write a function to calculate Sum of A and B\nint PlayerFunction(int a, int b){\n\n\n\n\n\n\n}", "Arial", 20);
	labelQuestion->setPosition(visibleSize.width / 2, visibleSize.height-200);
	this->addChild(labelQuestion);


	//TextField
	Hello::textFieldCode = ui::TextField::create("Enter your code", "Arial", 30);
	Hello::textFieldCode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 200));
	this->addChild(textFieldCode);
	Hello::functionName = "int PlayerFunction(int a, int b)";
	textFieldCode->addEventListener(CC_CALLBACK_2(Hello::TextFieldEvent, this));
	
	//Button
	Hello::button = cocos2d::ui::Button::create();
	button->setTitleText("Click here to compile");
	button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 500));
	button->addTouchEventListener(CC_CALLBACK_2(Hello::ButtonTouchEvent, this));
	this->addChild(button);



	/*{
		lua_State* L = luaL_newstate();
		luaL_dostring(L, "a = 1");
		lua_getglobal(L, "x");
		lua_Number x = lua_tonumber(L, 1);
		CCLOG("%d", (int)x);
	}*/

  
    return true;
}


void Hello::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Hello::CreateFileToPlayerCode(std::string content, std::string functionName){
	//.h template
	fstream fout;
	fout.open("..\\Classes\\PlayerCode.h");
	fout << "#pragma once\n " << functionName << ";";
	fout.close();
	//.cpp template
	fout.open("..\\Classes\\PlayerCode.cpp");
	fout << "#include \"PlayerCode.h\"\n" << "using namespace std;\n"
		<< functionName << "{\n" << content << "\n";
	fout.close();
}

void Hello::ExcutePlayerCode(std::string content, std::string functionName){
	Hello::CreateFileToPlayerCode(content, functionName);
	try{
		int result = PlayerFunction(2,3);
		auto myLabel = Label::createWithSystemFont("Run function PlayerFunction(2,3)\nYour result is: " + std::to_string(result), "Arial", 16);
		myLabel->setPosition(button->getPosition() - Vec2(0,50));
		
		this->addChild(myLabel);
	}
	catch (string somethingError){
		auto myLabel = Label::createWithSystemFont(somethingError, "Arial", 16);
		myLabel->setPosition(button->getPosition() - Vec2(0, 50));
		this->addChild(myLabel);
	}
}

void Hello::TextFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type){
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
		break;
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
		break;
	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
		Hello::content = Hello::textFieldCode->getString();
		CCLOG("%s", Hello::content.c_str());
		break;
	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
		break;
	default:
		break;
	}
}

void Hello::ButtonTouchEvent(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		CCLOG("%s", Hello::textFieldCode->getString().c_str());
		Hello::ExcutePlayerCode(Hello::content, Hello::functionName);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}