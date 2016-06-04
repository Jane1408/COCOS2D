#include "Bullet.h"
#include "Definitions.h"

std::string GetBulletFile(CBullet::Type const& type)
{
	switch (type)
	{
	case CBullet::Normal: return "bull.jpg";
	case CBullet::Fast: return "fast_bull.jpg";
	case CBullet::Power: return "power_bull.jpg";
	}
}

CBullet * CBullet::create(bool isHero, cocos2d::Point const& position, CBullet::Type type)

{
	CBullet* pSprite = new CBullet();
	pSprite->setPosition(position);
	pSprite->m_type = type;
	std::string str;
	if (isHero)
	{
		pSprite->m_direction = 1;
		str = "hero_bullet.png";
		pSprite->m_bitmask = BULLET_BITMASK;
	}
	else
	{
		pSprite->m_direction = -1;
		str = GetBulletFile(type);
		pSprite->m_bitmask = ENEMY_BULLET_BITMASK;
	}

	if (pSprite->initWithFile(str))
	{
		pSprite->autorelease();

		pSprite->initOptions();

		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}


void CBullet::Update(float dt)
{
	if (this->getPosition().y > this->getParent()->getBoundingBox().size.height || this->getPosition().y < 0)
	{
		this->Kill();
	}
	else
	{
		auto yPos = this->getPosition().y + m_Speed * m_direction;
		this->setPosition(this->getPosition().x, yPos);
	}
	if (!IsLife())
	{
		this->Destroy();
	}
}

void CBullet::SetParams()
{
	switch (m_type)
	{
	case CBullet::Normal: m_Speed = 10; SetDamage(10); break;
	case CBullet::Fast: m_Speed = 20; SetDamage(10); break;
	case CBullet::Power: m_Speed = 7; SetDamage(30); break;
	}
}

void CBullet::initOptions()
{
	this->SetParams();
	this->SetHealthPoint(1);
	this->schedule(schedule_selector(CBullet::Update), 1 / 60);

	auto playerPhysicsBoby = cocos2d::PhysicsBody::createBox(this->getContentSize());
	playerPhysicsBoby->setCollisionBitmask(m_bitmask);
	playerPhysicsBoby->setContactTestBitmask(true);
	playerPhysicsBoby->setGravityEnable(false);
	playerPhysicsBoby->setDynamic(true);
	this->setPhysicsBody(playerPhysicsBoby);
}

CBullet::CBullet() = default;
