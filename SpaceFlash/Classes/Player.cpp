#include "Player.h"
#include "Bullet.h"
#include "Definitions.h"

Player::Player() = default;

void Player::Shoot(float dt)
{
	auto bul = CBullet::create(true, this->getPosition(), CBullet::HeroNormal);
	this->getParent()->addChild(bul);
	if (m_isDoubleShooting)
	{
		cocos2d::Vec2 pos = { this->getPosition().x - 44, this->getPosition().y };
		bul = CBullet::create(true, pos, CBullet::Rocket);
		this->getParent()->addChild(bul);
		pos.x += 88;
		bul = CBullet::create(true, pos, CBullet::Rocket);
		this->getParent()->addChild(bul);
	}
}

void Player::initOptions()
{
	this->m_isDoubleShooting = false;
	this->m_isImmortal = false;
	this->SetHealthPoint(PLAYER_HEALTH);
	this->m_isShooting = false;
	auto playerPhysicsBoby = cocos2d::PhysicsBody::createBox(this->getContentSize());
	playerPhysicsBoby->setCollisionBitmask(PLAYER_BITMASK);
	playerPhysicsBoby->setContactTestBitmask(true);
	playerPhysicsBoby->setDynamic(false);
	this->setPhysicsBody(playerPhysicsBoby);
	this->schedule(schedule_selector(Player::Update), float(1 / 60));

	m_activeShield = new Sprite();
	m_activeShield->initWithFile(ACTIVE_SHIELD);
}




Player * Player::create()

{
	Player* pSprite = new Player();
	if (pSprite->initWithFile(HERO_IMG))
	{
		pSprite->autorelease();
		pSprite->initOptions();
		pSprite->initExplosionAnim();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

void Player::Update(float dt)
{
	if (!IsLife() && IsDeadDone())
	{
		Destroy();
		cocos2d::EventCustom event(END_GAME);
		cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}

void Player::StartShooting()
{
	m_isShooting = true;
	this->schedule(schedule_selector(Player::Shoot), 0.2f);
}

void Player::StopShooting()
{
	m_isShooting = false;
	this->unschedule(schedule_selector(Player::Shoot));
}

void Player::UpdateVisualHeals()
{
	auto health = GetHealth();
	health < 0 ? health = 0 : health;
	m_healthLine->setScaleX(health / PLAYER_HEALTH);
}

void Player::SetVisualHealth()
{
	m_healthLine = new Sprite();
	m_healthLine->initWithFile(HP_LINE);
	m_healthLine->setPosition({ this->getParent()->getContentSize().width / 2, m_healthLine->getContentSize().height / 2 });
	this->getParent()->addChild(m_healthLine);
}

void Player::AddHealth()
{
	SetHealthPoint(GetHealth() + BONUCE_HEALTH);
	UpdateVisualHeals();
}

void Player::StartDoubleShooting()
{
	m_isDoubleShooting = true;
	this->scheduleOnce(schedule_selector(Player::StopDoubleShooting), BONUCE_TIME);
}

void Player::StopDoubleShooting(float dt)
{
	m_isDoubleShooting = false;
}

void Player::StartImmortal()
{
	m_isImmortal = true;
	auto pos = this->getParent()->getContentSize();
	m_activeShield->setPosition(pos.width - m_activeShield->getContentSize().width / 2, m_activeShield->getContentSize().height / 2);
	this->getParent()->addChild(m_activeShield);
	this->scheduleOnce(schedule_selector(Player::StopImmortal), BONUCE_TIME);
}

void Player::StopImmortal(float dt)
{
	m_activeShield->removeFromParentAndCleanup(true);
	m_isImmortal = false;
}

bool Player::IsImmortal()
{
	return m_isImmortal;
}

void Player::initExplosionAnim()
{
	cocos2d::SpriteFrameCache *sharedSpriteFrameCache = cocos2d::SpriteFrameCache::getInstance();

	auto animFrames = cocos2d::Vector<cocos2d::SpriteFrame*>(20);

	animFrames.clear();
	char str[100] = { 0 };

	for (int i = 1; i < 9; i++)
	{
		sprintf(str, "enemy_explosion_%02d.png", i);
		cocos2d::SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.05f);
	m_explosion = cocos2d::Animate::create(animation);
	SetdeadAnimate(m_explosion);
}




