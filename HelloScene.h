#ifndef __HELLO_SCENE_H__
#define __HELLO_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
class Hello : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	void CreateFileToPlayerCode(std::string content, std::string functionName);
	void ExcutePlayerCode(std::string content, std::string functionName);
	void TextFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);
	void ButtonTouchEvent(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	std::string content;
	std::string functionName;
	cocos2d::ui::TextField *textFieldCode;
	cocos2d::ui::Button *button;
    // implement the "static create()" method manually
    CREATE_FUNC(Hello);
};

#endif // __HELLO_SCENE_H__
