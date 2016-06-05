#include "LoseScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;

int currentWave;

Scene* LoseScene::createScene(int wave)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	currentWave = wave;
	// 'layer' is an autorelease object
	auto layer = LoseScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoseScene::init()
{
	//1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgrowndSprite = Sprite::create(LOSE_SPLASH_IMG);
	backgrowndSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgrowndSprite);
	std::string str = "Death caught you\n on the " + std::to_string(currentWave) + " wave";
	auto waveLabel = Label::createWithTTF(str, MAIN_FONT, visibleSize.height * FONT_SIZE);
	waveLabel->setColor(Color3B::YELLOW);
	waveLabel->setPosition(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height * 0.7f);
	this->addChild(waveLabel);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LoseScene::GoToMenuScene, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool LoseScene::GoToMenuScene(Touch* touch, Event* event)
{
	auto scene = MainMenu::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	return true;
}

