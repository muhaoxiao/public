#include "SoundPlay.h"
using namespace CocosDenshion;
USING_NS_CC;

Layer* SoundPlay::createScene()
{
    auto * layer = SoundPlay::create();
	return layer;
}

// on "init" you need to initialize your instance
bool SoundPlay::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

    audioengine = SimpleAudioEngine::getInstance();
	audioengine->preloadBackgroundMusic("muse.mp3");
    Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	 
    auto closeItem = MenuItemImage::create(
                                           "close.png",
                                           "Close1.png",
										   CC_CALLBACK_1(SoundPlay::menuCloseCallback, this));
	auto LaunchItem = MenuItemImage::create(
                                           "launc.png",
                                           "launc1.png",
										   CC_CALLBACK_1(SoundPlay::menuLaunchCallback, this));
	auto resumeItem = MenuItemImage::create(
                                           "resume.png",
                                           "resume1.png",
										   CC_CALLBACK_1(SoundPlay::menuResumeCallback, this));
	auto pauseItem = MenuItemImage::create(
                                           "pause.png",
                                           "pause1.png",
										   CC_CALLBACK_1(SoundPlay::menuPauseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	LaunchItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 300,
		                         origin.y + closeItem->getContentSize().height / 2));

	pauseItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 200,
		                        origin.y + closeItem->getContentSize().height / 2));

	resumeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 100,
		                         origin.y + closeItem->getContentSize().height / 2));
    auto menu = Menu::create(closeItem,LaunchItem,pauseItem,resumeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = LabelTTF::create("Hello World", "Arial", 36);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                  origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
	
    auto sprite = Sprite::create("background.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite->setAnchorPoint(Vec2(0.5,0.5));
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(sprite, 0);

	InitBatteryLevel();
	ShowChinese();
    return true;
}


void SoundPlay::menuCloseCallback(Ref* pSender)
{
	audioengine->stopBackgroundMusic(true);
}
void SoundPlay::menuLaunchCallback(cocos2d::Ref* pSnder)
{
	audioengine->playBackgroundMusic("LemonTree.mp3",true);
}
void SoundPlay::menuPauseCallback(cocos2d::Ref* pSnder)
{
	audioengine->pauseBackgroundMusic();
}
void SoundPlay::menuResumeCallback(cocos2d::Ref* pSnder)
{

	//audioengine->resumeBackgroundMusic();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	static int number = 50;
	node->setPosition(Vec2(origin.x + number++, origin.y + 520));
}

static float s_level = -1;
void SoundPlay::InitBatteryLevel()
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	node = cocos2d::Node::create();
	this->addChild(node,2);
	node->setPosition(Vec2(origin.x + 50, origin.y + 520));
	auto ct = Sprite::create("widget/BL_content.png");
	ct->setPosition(Vec2(-1, 0));
	auto bg = Sprite::create("widget/BL_bg.png");
	node->addChild(bg);
	node->addChild(ct);
	//node->setVisible(false);
#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
#endif
}

void SoundPlay::ShowChinese()
{
	//创建立词典实列,将xml文件加载到词典中
	auto *chnString = Dictionary::createWithContentsOfFile("String.xml");
	//通过xml文件中的key获取value、
	const char *str1 = ((String*)chnString->objectForKey("string1"))->getCString();
	auto * label1 = Label::create(str1,"Arial",36);
	label1->setPosition(320, 270);
	addChild(label1);
}