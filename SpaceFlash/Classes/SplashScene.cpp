#include "SplashScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SplashScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SplashScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
	//1. super init first
	if (!Layer::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BONUCE_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SHOOT_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(D_SHOOT_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(ROCKET_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(EXPLOSION_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(BOSS_EXPLOSION_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(GAMEOVER_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_SOUND.c_str());

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->scheduleOnce(schedule_selector(SplashScene::GoToMenuScene), 2);

	auto backgrowndSprite = Sprite::create(SPLASH_IMG);
	backgrowndSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgrowndSprite);

	return true;
}

void SplashScene::GoToMenuScene(float dt)
{
	auto scene = MainMenu::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

