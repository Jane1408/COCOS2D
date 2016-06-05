#include "Enemy.h"
#include "Definitions.h"
#include "Bonuse.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

std::string GetEnemyFile(CEnemy::Type const& type)
{
	switch (type)
	{
	case CEnemy::Common : return COMMON_IMG;
	case CEnemy::DoubleCommon : return DOUBLE_COMMON_IMG;
	case CEnemy::HeavyCommon : return HEAVY_COMMON_IMG;
	case CEnemy::FastDouble : return FAST_DOUBLE_IMG;
	case CEnemy::PowerDouble : return POWER_DOUBLE_IMG;
	case CEnemy::VeryHeavy : return VERY_HEAVY_IMG;
	case CEnemy::FIRST_BOSS: return FIRST_BOSS_IMG;
	case CEnemy::SECOND_BOSS: return SECOND_BOSS_IMG;
	case CEnemy::THIRD_BOSS: return THIRD_BOSS_IMG;
	default: return COMMON_IMG;

	}
}

CEnemy * CEnemy::create(cocos2d::Point const& position, Type type)
{
	CEnemy* pSprite = new CEnemy();
	pSprite->m_type = type;
	pSprite->setPosition({ position.x, position.y + ENEMY_DELTA_START });
	pSprite->m_startEntering = cocos2d::MoveTo::create(2, position);
	if (pSprite->initWithFile(GetEnemyFile(type)))
	{
		pSprite->autorelease();

		pSprite->initOptions();
		pSprite->initExplosionAnim();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

cocos2d::Sequence * GetSeqMove()
{
	int index = cocos2d::RandomHelper::random_int(1, 6);

	auto right = cocos2d::MoveBy::create(2, cocos2d::Vec2(100, 0));
	auto left = cocos2d::MoveBy::create(2, cocos2d::Vec2(-100, 0));
	auto up = cocos2d::MoveBy::create(1, cocos2d::Vec2(0, 50));
	auto down = cocos2d::MoveBy::create(2, cocos2d::Vec2(0, -50));
	auto delay = cocos2d::DelayTime::create(0.1f);
	switch (index)
	{
	case 1: return cocos2d::Sequence::create(right, delay, left, delay, left, delay, right, nullptr);
	case 2: return cocos2d::Sequence::create(left, delay, right, delay, right, delay, left, nullptr);
	case 3: return cocos2d::Sequence::create(right, delay, down, delay, left, delay, up, nullptr);
	case 4: return cocos2d::Sequence::create(left, delay, down, delay, right, delay, up, nullptr);
	case 5: return cocos2d::Sequence::create(right, delay, down, delay, left, delay, left, delay, up, delay, right, nullptr);
	case 6: return cocos2d::Sequence::create(left, delay, down, delay, right, delay, right, delay, up, delay, left, nullptr);
	default : return cocos2d::Sequence::create(right, delay, left, delay, left, delay, right, nullptr);
	}
}

void CEnemy::Update(float dt)
{
	if (!m_isReady && m_startEntering->isDone())
	{
		m_isReady = true;
		this->runAction(cocos2d::RepeatForever::create(GetSeqMove()));
	}
	if (!IsLife())
	{
		if (IsDeadDone())
		{
			if (cocos2d::RandomHelper::random_int(1, 5) == 1)
			{
				this->getParent()->addChild(CBonuce::create(this->getPosition()));
			}
			if (m_type >= FIRST_BOSS)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BOSS_EXPLOSION_SOUND.c_str());
			}
			else
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(EXPLOSION_SOUND.c_str());
			}
			Destroy();
		}
	}
}

float GetShootingFrequency(CEnemy::Type const& type)
{
	switch (type)
	{
	case CEnemy::Common: return COMMON_SF;
	case CEnemy::DoubleCommon: return DOUBLE_COMMON_SF;
	case CEnemy::HeavyCommon: return HEAVY_COMMON_SF;
	case CEnemy::FastDouble: return FAST_DOUBLE_SF;
	case CEnemy::PowerDouble: return POWER_DOUBLE_SF;
	case CEnemy::VeryHeavy: return VERY_HEAVY_SF;
	case CEnemy::FIRST_BOSS: return FIRST_BOSS_SF;
	case CEnemy::SECOND_BOSS: return SECOND_BOSS_SF;
	case CEnemy::THIRD_BOSS: return THIRD_BOSS_SF;
	default : return COMMON_SF;
	}
}

float GetHealthPoint(CEnemy::Type const& type)
{
	switch (type)
	{
	case CEnemy::Common: return COMMON_HP;
	case CEnemy::DoubleCommon: return DOUBLE_COMMON_HP;
	case CEnemy::HeavyCommon: return HEAVY_COMMON_HP;
	case CEnemy::FastDouble: return FAST_DOUBLE_HP;
	case CEnemy::PowerDouble: return POWER_DOUBLE_HP;
	case CEnemy::VeryHeavy: return VERY_HEAVY_HP;
	case CEnemy::FIRST_BOSS: return FIRST_BOSS_HP;
	case CEnemy::SECOND_BOSS: return SECOND_BOSS_HP;
	case CEnemy::THIRD_BOSS: return THIRD_BOSS_HP;
	default: return COMMON_HP;

	}
}

void CEnemy::initOptions()
{
	m_isReady = false;
	this->SetSpeed(40);
	this->SetDamage(50);
	this->SetHealthPoint(GetHealthPoint(m_type));
	this->schedule(schedule_selector(CEnemy::Update), 1 / 60);
	this->schedule(schedule_selector(CEnemy::Shoot), GetShootingFrequency(m_type));
	this->runAction(m_startEntering);
	this->SetGuns();

	auto playerPhysicsBoby = cocos2d::PhysicsBody::createBox(this->getContentSize());
	playerPhysicsBoby->setCollisionBitmask(ENEMY_BITMASK);
	playerPhysicsBoby->setContactTestBitmask(true);
	playerPhysicsBoby->setDynamic(false);
	this->setPhysicsBody(playerPhysicsBoby);
}

void CEnemy::initExplosionAnim()
{
	SpriteFrameCache *sharedSpriteFrameCache = SpriteFrameCache::getInstance();

	auto animFrames = Vector<SpriteFrame*>(20);
	char str[100] = { 0 };

	if (m_type >= FIRST_BOSS)
	{
		for (int i = 1; i < 7; i++)
		{
			sprintf(str, "explosion_boss_%02d.png", i);
			SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
			animFrames.pushBack(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.08f);
		m_explosion = Animate::create(animation);
	}
	else
	{
		animFrames.clear();

		for (int i = 1; i < 9; i++)
		{
			sprintf(str, "enemy_explosion_%02d.png", i);
			SpriteFrame* frame = sharedSpriteFrameCache->getSpriteFrameByName(str);
			animFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
		m_explosion = Animate::create(animation);
	}
	SetdeadAnimate(m_explosion);
}

void CEnemy::SetSpeed(float speed)
{
	m_speed = speed;
}

void CEnemy::SetGuns()
{
	switch (m_type)
	{
	case CEnemy::Common: m_gunsSlots = ONE_SLOT; break;
	case CEnemy::DoubleCommon: m_gunsSlots = COMMON_DOUBLE_SLOTS; break;
	case CEnemy::HeavyCommon: m_gunsSlots = ONE_SLOT; break;
	case CEnemy::FastDouble: m_gunsSlots = FAST_DOUBLE_SLOTS; break;
	case CEnemy::PowerDouble: m_gunsSlots = POWER_DOUBLE_SLOTS; break;
	case CEnemy::VeryHeavy: m_gunsSlots = ONE_SLOT; break;
	}
	
}

CBullet::Type GetBullettype(CEnemy::Type type)
{
	switch (type)
	{
	case CEnemy::Common: return CBullet::Type::Normal;
	case CEnemy::DoubleCommon: return CBullet::Type::Normal;
	case CEnemy::HeavyCommon: return CBullet::Type::Normal;
	case CEnemy::FastDouble: return CBullet::Type::Fast;
	case CEnemy::PowerDouble: return CBullet::Type::Power;
	case CEnemy::VeryHeavy: return CBullet::Type::Power;
	default: return CBullet::Type::Normal;
	}
}

std::vector<std::pair<CBullet::Type, int>> GetBossSlots(CEnemy::Type const& type)
{
	switch (type)
	{
	case CEnemy::FIRST_BOSS: return FIRST_BOSS_SLOTS;
	case CEnemy::SECOND_BOSS: return SECOND_BOSS_SLOTS;
	case CEnemy::THIRD_BOSS: return THIRD_BOSS_SLOTS;
	default: return FIRST_BOSS_SLOTS;
	}
}

void CEnemy::Shoot(float dt)
{
	if (m_type < FIRST_BOSS)
	{
		for (auto &it : m_gunsSlots)
		{
			cocos2d::Vec2 pos = { this->getPosition().x - it, this->getPosition().y };
			auto bul = CBullet::create(false, pos, GetBullettype(m_type));
			this->getParent()->addChild(bul);
		}
	}
	else
	{
		for (auto &it : GetBossSlots(m_type))
		{
			cocos2d::Vec2 pos = { this->getPosition().x - it.second, this->getPosition().y };
			auto bul = CBullet::create(false, pos, it.first);
			this->getParent()->addChild(bul);
		}
	}
}

CEnemy::CEnemy() = default;


