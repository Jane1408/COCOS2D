#include "Enemy.h"
#include "Definitions.h"


std::string GetEnemyFile(CEnemy::Type const& type)
{
	switch (type)
	{
	case CEnemy::Common : return "enemy_space_ship1.png";
	case CEnemy::DoubleCommon : return "enemy_space_ship3.png";
	case CEnemy::HeavyCommon : return "enemy_space_ship2.png";
	case CEnemy::FastDouble : return "enemy_space_ship4.png";
	case CEnemy::PowerDouble : return "enemy_space_ship5.png";
	case CEnemy::VeryHeavy : return "enemy_space_ship6.png";
	case CEnemy::FIRST_BOSS: return "enemy_boss.png";
	case CEnemy::SECOND_BOSS: return "enemy_boss2.png";
	case CEnemy::THIRD_BOSS: return "enemy_boss3.png";

	}
}

CEnemy * CEnemy::create(cocos2d::Point const& position, Type type)
{
	CEnemy* pSprite = new CEnemy();
	pSprite->m_type = type;
	pSprite->setPosition({ position.x, position.y + 200 });
	pSprite->m_startEntering = cocos2d::MoveTo::create(2, position);
	if (pSprite->initWithFile(GetEnemyFile(type)))
	{
		pSprite->autorelease();

		pSprite->initOptions();

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
		Destroy();
	}
}

float GetShootingFrequency(CEnemy::Type const& type)
{
	switch (type)
	{
	case CEnemy::Common: return 0.6f;
	case CEnemy::DoubleCommon: return 0.75f;
	case CEnemy::HeavyCommon: return 0.6f;
	case CEnemy::FastDouble: return 0.9f;
	case CEnemy::PowerDouble: return 1.2f;
	case CEnemy::VeryHeavy: return 0.9;
	case CEnemy::FIRST_BOSS: return 0.8;
	case CEnemy::SECOND_BOSS: return 0.7;
	case CEnemy::THIRD_BOSS: return 0.6;

	}
}

float GetHealthPoint(CEnemy::Type const& type)
{
	switch (type)
	{
	case CEnemy::Common: return 60.0f;
	case CEnemy::DoubleCommon: return 60.0f;
	case CEnemy::HeavyCommon: return 100.0f;
	case CEnemy::FastDouble: return 120.0f;
	case CEnemy::PowerDouble: return 120.f;
	case CEnemy::VeryHeavy: return 200.0f;
	case CEnemy::FIRST_BOSS: return 350.0f;
	case CEnemy::SECOND_BOSS: return 550.0f;
	case CEnemy::THIRD_BOSS: return 700.0f;

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

	}
}

std::vector<std::pair<CBullet::Type, int>> GetBossSlots(CEnemy::Type const& type)
{
	switch (type)
	{
	case CEnemy::FIRST_BOSS: return FIRST_BOSS_SLOTS;
	case CEnemy::SECOND_BOSS: return SECOND_BOSS_SLOTS;
	case CEnemy::THIRD_BOSS: return THIRD_BOSS_SLOTS;
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


