#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "string"
#include "vector"
#include "map"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"                      //������չ��
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
	//�����̵����༭���ý���ʱ����
	virtual void editBoxEditingDidBegin(EditBox * editBoxt);
	//��������Ϣ�༭��ʧȥ����ʱ����
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	//���༭����ı��ı�ʱ����
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
	//�����ؼ�����ʱ���ߵ���˼������������ʱ����
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
