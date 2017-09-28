#include "HelloWorldScene.h"
#include "SoundPlay.h"
#include "stdlib.h"
#include "time.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto * layer = HelloWorld::create();
	auto * layer1 = SoundPlay::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
	srand(time(0));
	LayerColor::initWithColor(ccc4(255, 255, 255, 255));
    
	m_size = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	editBox = EditBox::create(Size(300,40),
		      Scale9Sprite::create("item_bg.png"),
			  Scale9Sprite::create("old_item.png"));
	editBox->setPosition(Vec2(m_size.width / 2, 50));
	this->addChild(editBox,30);
	//设置预置文本
	editBox->setPlaceHolder("please input:");
	//设置文本颜色
	editBox->setFontColor(Color3B(100,100,100));
	//设置最大长充，win32无效，android 下可用
	editBox->setMaxLength(10);
	//设置输入风格/*开启任何输入类型键盘包括换行*/
	editBox->setInputMode(EditBox::InputMode::ANY);
	//设置输入标志/*密码*/
	editBox->setInputFlag(EditBox::InputFlag::PASSWORD);
	//设置键盘中return键显示的字符，这个移植android的时候没有看出来
	editBox->setReturnType(EditBox::KeyboardReturnType::GO);
	//写上这句话的时候以下的四个函数才会被调用
	editBox->setEnabled(false);
	editBox->setDelegate(this);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));   
	auto _closeItem = MenuItemImage::create(
		                                   "resume.png",
		                                   "resume1.png",
										   CC_CALLBACK_1(HelloWorld::startButton, this));
	closeItem->setPosition(Vec2(origin.x + m_size.width - closeItem->getContentSize().width / 2,
                                origin.y + closeItem->getContentSize().height/2));
	_closeItem->setPosition(Vec2(250,50));


	auto menu = Menu::create(closeItem, _closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	
    auto * label = LabelTTF::create("Hello World", "Arial", 34);
	label->setPosition(Vec2(origin.x + m_size.width / 2,
		                           origin.y + m_size.height - label->getContentSize().height));
	label->setColor(Color3B(0,0,0));
    this->addChild(label, 1);
	
    auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(m_size.width / 2 + origin.x, m_size.height / 2 + origin.y));
    this->addChild(sprite, 0);

	//创建立词典实列,将xml文件加载到词典中
	chnString = Dictionary::createWithContentsOfFile("String.xml");
	//初始化输出文本
	textOutput = Label::create("", "Arial", 30);
	textOutput->setColor(Color3B(0, 0, 0));
	textOutput->setPosition(Vec2(m_size.width / 2 + origin.x, 150));
	addChild(textOutput, 10);

	hengFu = Label::create("", "Arial", 30);
	hengFu->setPosition(Vec2(m_size.width / 2 + origin.x, m_size.height-135));
	addChild(hengFu, 10);

	initData();
    return true;
}

void HelloWorld::editBoxEditingDidBegin(EditBox * editBox)
{
	CCLog("begin!");
	CCLabelTTF * ttf = CCLabelTTF::create("begin","",24);
	ttf->setPosition(ccp(m_size.width/4,m_size.height*1/5));
//	this->addChild(ttf,10);
}

void HelloWorld::editBoxEditingDidEnd(EditBox * editBox)
{
	CCLog("end!");
	CCLabelTTF * ttf = CCLabelTTF::create("end", "", 24);
	ttf->setPosition(ccp(m_size.width / 4, m_size.height * 4 / 5));
//	this->addChild(ttf,10);
}

void HelloWorld::editBoxTextChanged(EditBox * editBox, const std::string & text)
{
	CCLog("textChanged!");
	CCLabelTTF * ttf = CCLabelTTF::create("textChanged!", "", 24);
	ttf->setPosition(ccp(m_size.width / 4, m_size.height * 3 / 5));
//	this->addChild(ttf,10);

	string src = editBox->getText(); 
	GameLogic(src);
}

void HelloWorld::editBoxReturn(EditBox * editBox)
{
	CCLog("return");
	CCLabelTTF * ttf = CCLabelTTF::create("return", "", 24);
	ttf->setPosition(ccp(m_size.width / 4, m_size.height * 2 / 5));
//	this->addChild(ttf, 10);

	char * str = (char *)this->editBox->getText();
	CCLabelTTF * text = CCLabelTTF::create(str, "", 24);
	text->setPosition(ccp(m_size.width / 2, m_size.height * 2 / 5));
//	this->addChild(text, 10);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif 
}

void HelloWorld::startButton(Ref* pSender)
{
	if (work_count.empty())
	{
		textOutput->setString("");
		init();
	}
	unsigned char num = rand() % work_count.size();
	strText = ch[num];
	textOutput->setString(ch[num]);
	editBox->setEnabled(true);
}

void HelloWorld::GameLogic(string text)
{
	auto target = work_count.find(strText);
	if (text == target->second)
	{
		hengFu->setColor(Color3B(75, 137, 1));
		hengFu->setString("answer true!");
		work_count.erase(target);
		ReloadArray();      //刷新数据
		if (!work_count.empty())  //不为空时
		{
			startButton(this);  //接着游戏
		}
	}
	else
	{
		hengFu->setColor(Color3B(219, 2, 12));
		hengFu->setString("Please re - enter!");
	}
}
void HelloWorld::initData(void)
{
	for (int i = 0; i < 12; i++)
	{
		string emp = String::createWithFormat("string%d", i)->getCString();;
		string  value = ((String*)chnString->objectForKey(emp))->getCString();
		string temp = String::createWithFormat("name%d", i)->getCString();;
		string  key = ((String*)chnString->objectForKey(temp))->getCString();
		work_count[value] = key;
		ReloadArray();
	}
}
void HelloWorld::ReloadArray()
{
	ch.clear();
	if (work_count.empty())
	{
		editBox->setEnabled(false);
		chnString = Dictionary::createWithContentsOfFile("String.xml");
		string  str2 = ((String*)chnString->objectForKey("TextOutput"))->getCString();
		textOutput->setString(str2);
		textOutput->setColor(Color3B(230, 88, 1));
		return;
	}
	auto it = work_count.begin();
	for (; it != work_count.end(); it++)
	{
		ch.push_back(it->first);
	}
}