#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"


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
	m_visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgrowndSprite = Sprite::create("BG.jpg");
	backgrowndSprite->setPosition(Point(m_visibleSize.width / 2 + origin.x, m_visibleSize.height / 2 + origin.y));
	this->addChild(backgrowndSprite);

	m_player = Player::create();
	m_player->setPosition(m_visibleSize.width / 2, m_player->getBoundingBox().size.height);
	this->addChild(m_player);
	m_player->SetVisualHealth();
	commander = WaveCommander::create(this);
	this->schedule(schedule_selector(GameScene::CheckWave), 1);

	/*auto enemy4 = CEnemy::create({ m_visibleSize.width / 2, m_visibleSize.height - 40 }, CEnemy::FastDouble);
	this->addChild(enemy4);

	auto enemy3 = CEnemy::create({ m_visibleSize.width / 2 - 120, m_visibleSize.height - 40 }, CEnemy::DoubleCommon);
	this->addChild(enemy3);

	auto enemy2 = CEnemy::create({ m_visibleSize.width / 2 - 240, m_visibleSize.height - 40 }, CEnemy::HeavyCommon);
	this->addChild(enemy2);

	auto enemy1 = CEnemy::create({ m_visibleSize.width / 2 - 360, m_visibleSize.height - 40 }, CEnemy::Common);
	this->addChild(enemy1);

	auto enemy5 = CEnemy::create({ m_visibleSize.width / 2 + 120, m_visibleSize.height - 40 }, CEnemy::PowerDouble);
	this->addChild(enemy5);

	auto enemy6 = CEnemy::create({ m_visibleSize.width / 2 + 240, m_visibleSize.height - 40 }, CEnemy::VeryHeavy);
	this->addChild(enemy6);*/

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

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
		player->Demaged(bullet->GetDamage());
		player->UpdateVisualHeals();
		bullet->Kill();
	}
	else if (firstBitmask == PLAYER_BITMASK && secondBitmask == ENEMY_BULLET_BITMASK)
	{
		auto player = static_cast<Player*>(first.getNode());
		auto bullet = static_cast<CEntity*>(second.getNode());
		player->Demaged(bullet->GetDamage());
		player->UpdateVisualHeals();
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
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact & contact)
{
	PhysicsBody *first = contact.getShapeA()->getBody();
	PhysicsBody *second = contact.getShapeB()->getBody();
	CheckGameCollision(*first, *second);
	return true;

}


