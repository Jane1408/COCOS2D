#include "Player.h"
#include "Bullet.h"
#include "Definitions.h"

Player::Player() = default;

void Player::Shoot(float dt)
{
	cocos2d::Vec2 pos = { this->getPosition().x - 44, this->getPosition().y };
	auto bul = CBullet::create(true, pos, CBullet::Normal);
	this->getParent()->addChild(bul);
	pos.x += 88;
	auto bul1 = CBullet::create(true, pos, CBullet::Normal);
	this->getParent()->addChild(bul1);
}

void Player::initOptions()
{
	this->SetDamage(20);
	this->SetHealthPoint(300);
	this->m_isShooting = false;
	auto playerPhysicsBoby = cocos2d::PhysicsBody::createBox(this->getContentSize());
	playerPhysicsBoby->setCollisionBitmask(PLAYER_BITMASK);
	playerPhysicsBoby->setContactTestBitmask(true);
	playerPhysicsBoby->setDynamic(false);
	this->setPhysicsBody(playerPhysicsBoby);
	this->schedule(schedule_selector(Player::Update), 1 / 60);
}




Player * Player::create()

{
	Player* pSprite = new Player();
	if (pSprite->initWithFile("hero_spase_ship.png"))
	{
		pSprite->autorelease();
		pSprite->initOptions();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

void Player::Update(float dt)
{
	if (!IsLife())
	{
		Destroy();
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
	m_healthLine->initWithFile("health.jpg");
	m_healthLine->setPosition({ this->getParent()->getContentSize().width / 2, m_healthLine->getContentSize().height / 2 });
	this->getParent()->addChild(m_healthLine);
}






