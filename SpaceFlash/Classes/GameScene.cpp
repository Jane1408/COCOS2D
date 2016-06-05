#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"
#include "LoseScene.h"
#include "WinScene.h"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	// add layer as a child to scene
	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//1. super init first
	if (!Layer::init())
	{
		return false;
	}

	/*CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(POINT_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(LOSE_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(DROP_SOUND.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_SOUND.c_str());*/

	AddPlists();
	InitLayer();
	this->schedule(schedule_selector(GameScene::CheckWave), 1);
	SetListeners();
	return true;
}

void GameScene::CheckWave(float dt)
{
	commander->Update(dt);
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	auto location = touch->getLocation();

	if (m_player->getBoundingBox().containsPoint(location))
	{
		m_player->StartShooting();
		m_player->setPosition(touch->getLocation().x, m_player->getPosition().y);
		return true;
	}
	return false;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
	if (touch->getLocation().x >= m_visibleSize.width - m_player->getContentSize().width / 2)
	{
		m_player->setPosition(m_visibleSize.width - m_player->getContentSize().width / 2, m_player->getPosition().y);
	}
	else if (touch->getLocation().x <= m_player->getContentSize().width / 2)
	{
		m_player->setPosition(m_player->getContentSize().width / 2, m_player->getPosition().y);
	}
	else
	{
		m_player->setPosition(touch->getLocation().x, m_player->getPosition().y);
	}

}

void GameScene::onTouchEnded(Touch * touch, Event * event)
{
	m_player->StopShooting();
}



void GameScene::CheckGameCollision(cocos2d::PhysicsBody & first, cocos2d::PhysicsBody & second)
{
	auto firstBitmask = first.getCollisionBitmask();
	auto secondBitmask = second.getCollisionBitmask();

	if (firstBitmask == BULLET_BITMASK && secondBitmask == ENEMY_BITMASK)
	{
		auto enemy = static_cast<CEntity*>(second.getNode());
		auto bullet = static_cast<CEntity*>(first.getNode());
		enemy->Demaged(bullet->GetDamage());
		bullet->Kill();
	}
	else if (firstBitmask == ENEMY_BITMASK && secondBitmask == BULLET_BITMASK)
	{
		auto enemy = static_cast<CEntity*>(first.getNode());
		auto bullet = static_cast<CEntity*>(second.getNode());
		enemy->Demaged(bullet->GetDamage());
		bullet->Kill();
	}
	else if (firstBitmask == ENEMY_BULLET_BITMASK && secondBitmask == PLAYER_BITMASK)
	{
		auto player = static_cast<Player*>(second.getNode());
		auto bullet = static_cast<CEntity*>(first.getNode());
		if (!player->IsImmortal())
		{
			player->Demaged(bullet->GetDamage());
			player->UpdateVisualHeals();
		}
		bullet->Kill();
	}
	else if (firstBitmask == PLAYER_BITMASK && secondBitmask == ENEMY_BULLET_BITMASK)
	{
		auto player = static_cast<Player*>(first.getNode());
		auto bullet = static_cast<CEntity*>(second.getNode());
		if (!player->IsImmortal())
		{
			player->Demaged(bullet->GetDamage());
			player->UpdateVisualHeals();
		}
		bullet->Kill();
	}
	else if (firstBitmask == ENEMY_BULLET_BITMASK && secondBitmask == BULLET_BITMASK)
	{
		static_cast<CEntity*>(second.getNode())->Kill();
		static_cast<CEntity*>(first.getNode())->Kill();
	}
	else if (firstBitmask == BULLET_BITMASK && secondBitmask == ENEMY_BULLET_BITMASK)
	{
		static_cast<CEntity*>(second.getNode())->Kill();
		static_cast<CEntity*>(first.getNode())->Kill();
	}
	///
	else if ((firstBitmask >= HEALTH_BITMASK && firstBitmask <= BOMB_BITMASK) 
		&& secondBitmask == PLAYER_BITMASK)
	{
		auto player = static_cast<Player*>(second.getNode());
		auto bonus = static_cast<CEntity*>(first.getNode());

		switch (firstBitmask)
		{
		case HEALTH_BITMASK: player->AddHealth(); break;
		case SHIELD_BITMASK: player->StartImmortal(); break;
		case POWER_BITMASK: player->StartDoubleShooting(); break;
		case BOMB_BITMASK: commander->KillAll(); break;
		}
		bonus->Kill();
	}
	else if (firstBitmask == PLAYER_BITMASK 
		&& (secondBitmask >= HEALTH_BITMASK && secondBitmask <= BOMB_BITMASK))
	{
		auto player = static_cast<Player*>(first.getNode());
		auto bonus = static_cast<CEntity*>(second.getNode());

		switch (secondBitmask)
		{
		case HEALTH_BITMASK: player->AddHealth(); break;
		case SHIELD_BITMASK: player->StartImmortal(); break;
		case POWER_BITMASK: player->StartDoubleShooting(); break;
		case BOMB_BITMASK: commander->KillAll(); break;
		}
		bonus->Kill();
	}
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact & contact)
{
	PhysicsBody *first = contact.getShapeA()->getBody();
	PhysicsBody *second = contact.getShapeB()->getBody();
	CheckGameCollision(*first, *second);
	return true;

}

void GameScene::AddPlists()
{
	SpriteFrameCache *sharedSpriteFrameCache = SpriteFrameCache::getInstance();
	sharedSpriteFrameCache->addSpriteFramesWithFile("boss_explosion.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("bullet_explosion.plist");
	sharedSpriteFrameCache->addSpriteFramesWithFile("ship_explosion.plist");
}

void GameScene::SetListeners()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto updateWaveListener = EventListenerCustom::create(UPDATE_WAVE_HP, [=](EventCustom *event)
	{
		commander->UpdateProgressLine();
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(updateWaveListener, this);

	auto endGameListener = EventListenerCustom::create(END_GAME, [=](EventCustom *event)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GAMEOVER_SOUND.c_str());
		GameScene::GoToLoseScene();
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(endGameListener, this);

	auto winGameListener = EventListenerCustom::create(WIN_GAME, [=](EventCustom *event)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(GAMEOVER_SOUND.c_str());
		GameScene::GoToWinScene();
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(winGameListener, this);

}

void GameScene::InitLayer()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgrowndSprite = Sprite::create(BG_IMG);
	backgrowndSprite->setPosition(Point(m_visibleSize.width / 2 + origin.x, m_visibleSize.height / 2 + origin.y));
	this->addChild(backgrowndSprite);

	m_player = Player::create();
	m_player->setPosition(m_visibleSize.width / 2, m_player->getBoundingBox().size.height);
	this->addChild(m_player);
	m_player->SetVisualHealth();
	commander = WaveCommander::create(this);
}

void GameScene::GoToLoseScene()
{
	auto scene = LoseScene::createScene(commander->GetWaveNumber());

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameScene::GoToWinScene()
{
	auto scene = WinScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}