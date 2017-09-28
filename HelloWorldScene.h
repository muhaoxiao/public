#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "string"
#include "vector"
#include "map"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"                      //包含扩展库
using namespace cocos2d; 
using namespace cocos2d::extension;
using namespace std;

class HelloWorld : public cocos2d::LayerColor, public EditBoxDelegate
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init();  
	void GameLogic(string text);
	void initData();
	void ReloadArray();
    void menuCloseCallback(cocos2d::Ref* pSender);
	void startButton(cocos2d::Ref* pSender);
	CREATE_FUNC(HelloWorld);
	//当键盘弹出编辑框获得焦点时调用
	virtual void editBoxEditingDidBegin(EditBox * editBoxt);
	//当键盘消息编辑框失去焦点时调用
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	//当编辑框架文本改变时调用
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
	//当返回键按下时或者点击了键盘以外的区域时调用
	virtual void editBoxReturn(EditBox* editBox);
private:
	Vec2 origin;
	Size m_size;
	EditBox* editBox;
private:
	cocos2d::__Dictionary* chnString;
	map<string, string>  work_count;
	vector<string> ch;
	Label * textOutput;
	Label * hengFu;
	string  strText;
};

#endif // __HELLOWORLD_SCENE_H__
