#include "Bonuse.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

std::string GetBonuseFile(CBonuce::Type const& type)
{
	switch (type)
	{
	case CBonuce::Health: return HEALTH_IMG;
	case CBonuce::Shield: return SHIELD_IMG;
	case CBonuce::Power: return POWER_BONUCE_IMG;
	case CBonuce::Bomb: return BOMB_IMG;
	default: return HEALTH_IMG;
	}
}

CBonuce::Type GetType()
{
	auto num = cocos2d::RandomHelper::random_int(1, 4);
	switch (num)
	{
	case 1: return CBonuce::Health;
	case 2: return CBonuce::Shield;
	case 3: return CBonuce::Power;
	case 4: return CBonuce::Bomb;
	default: return CBonuce::Health;
	}
}

CBonuce * CBonuce::create(cocos2d::Point const& position)

{
	CBonuce* pSprite = new CBonuce();
	pSprite->m_type = GetType();
	pSprite->setPosition(position);

	if (pSprite->initWithFile(GetBonuseFile(pSprite->m_type)))
	{
		pSprite->autorelease();

		pSprite->initOptions();

		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}


void CBonuce::Update(float dt)
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
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BONUCE_SOUND.c_str());
		this->Destroy();
	}
}

int GetBitMask(CBonuce::Type type)
{
	switch (type)
	{
	case CBonuce::Health:
		return HEALTH_BITMASK;
	case CBonuce::Shield:
		return SHIELD_BITMASK;
	case CBonuce::Power:
		return POWER_BITMASK;
	case CBonuce::Bomb:
		return BOMB_BITMASK;
	default:
		return HEALTH_BITMASK;
	}
}

void CBonuce::initOptions()
{
	this->SetHealthPoint(1);
	this->schedule(schedule_selector(CBonuce::Update), float(1 / 60));

	auto PhysicsBoby = cocos2d::PhysicsBody::createBox(this->getContentSize());
	PhysicsBoby->setCollisionBitmask(GetBitMask(m_type));
	PhysicsBoby->setContactTestBitmask(true);
	PhysicsBoby->setGravityEnable(false);
	PhysicsBoby->setDynamic(true);
	this->setPhysicsBody(PhysicsBoby);
}

CBonuce::CBonuce() = default;
