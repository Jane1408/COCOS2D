#include "Bullet.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

std::string GetBulletFile(CBullet::Type const& type)
{
	switch (type)
	{
	case CBullet::Normal: return NORMAL_IMG;
	case CBullet::Fast: return FAST_IMG;
	case CBullet::Power: return POWER_IMG;
	case CBullet::Rocket: return ROCKET_IMG;
	case CBullet::HeroNormal: return HERO_NORMAL_IMG;
	default: return NORMAL_IMG;

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
		str = GetBulletFile(type);
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
		pSprite->initExplosionAnim();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}


void CBullet::Update(float dt)
{
	if (this->getPosition().y > this->getParent()->getBoundingBox().size.height + 20 || this->getPosition().y < -20)
	{
		this->Kill();
	}
	else if (IsLife())
	{
		auto yPos = this->getPosition().y + m_Speed * m_direction;
		this->setPosition(this->getPosition().x, yPos);
	}
	if (!IsLife() && IsDeadDone())
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
	case CBullet::HeroNormal: m_Speed = 10; SetDamage(10); break;
	case CBullet::Rocket: m_Speed = 9; SetDamage(15); break;

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

	switch (m_type)
	{
	case CBullet::Normal:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SHOOT_SOUND.c_str());
		break;
	case CBullet::Fast:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(D_SHOOT_SOUND.c_str());
		break;
	case CBullet::Power:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ROCKET_SOUND.c_str());
		break;
	case CBullet::Rocket:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ROCKET_SOUND.c_str());
		break;
	case CBullet::HeroNormal:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SHOOT_SOUND.c_str());
		break;
	default:
		break;
	}
}

void CBullet::initExplosionAnim()
{
	cocos2d::SpriteFrameCache *sharedSpriteFrameCache = cocos2d::SpriteFrameCache::getInstance();

	auto animFrames = cocos2d::Vector<cocos2d::SpriteFrame*>(20);

	char str[100] = { 0 };
	animFrames.clear();

	for (int i = 1; i < 15; i++)
	{
		sprintf(str, "bullet_explosion_%02d.png", i);
		cocos2d::SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	auto animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.05f);
	m_explosion = cocos2d::Animate::create(animation);
	SetdeadAnimate(m_explosion);
}

CBullet::CBullet() = default;
