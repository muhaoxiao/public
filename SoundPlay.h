#ifndef __SOUNDPLAY_H__
#define __SOUNDPLAY_H__
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
using namespace CocosDenshion;

class SoundPlay : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createScene();
    virtual bool init();  
    
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuLaunchCallback(cocos2d::Ref* pSnder);
	void menuPauseCallback(cocos2d::Ref* pSnder);
	void menuResumeCallback(cocos2d::Ref* pSnder);
    
    CREATE_FUNC(SoundPlay);
	SimpleAudioEngine * audioengine;
};

#endif // __SOUNDPLAY_H__
