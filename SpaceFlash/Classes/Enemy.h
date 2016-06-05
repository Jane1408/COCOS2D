#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include <vector>

const std::vector<std::pair<CBullet::Type, int>> FIRST_BOSS_SLOTS = { {CBullet::Normal, 55},{ CBullet::Normal ,-55},{ CBullet::Power ,0 } };
const std::vector<std::pair<CBullet::Type, int>> SECOND_BOSS_SLOTS = { { CBullet::Power, 45 },{ CBullet::Power ,-45 },{ CBullet::Fast ,0 } };
const std::vector<std::pair<CBullet::Type, int>> THIRD_BOSS_SLOTS = { { CBullet::Power, 58 },{ CBullet::Power ,-58 },{ CBullet::Normal, 40 },{ CBullet::Normal ,-40 }, { CBullet::Fast ,0 } };

class CEnemy : public CEntity
{
public: 
	enum Type 
	{
		Common = 0,
		HeavyCommon,
		DoubleCommon,
		FastDouble,
		PowerDouble,
		VeryHeavy,
		FIRST_BOSS,
		SECOND_BOSS,
		THIRD_BOSS,
	};

	static CEnemy *create(cocos2d::Point const& position, Type type);
	void Update(float dt) override;

protected:
	void SetSpeed(float speed);
	void SetGuns();
	void Shoot(float dt);
private:
	CEnemy();
	void initOptions();
	void initExplosionAnim();

	bool m_isReady;
	cocos2d::RefPtr<cocos2d::MoveTo> m_startEntering;
	Type m_type;
	float m_speed;
	std::vector<int> m_gunsSlots;
	cocos2d::RefPtr<cocos2d::Animate> m_explosion;
};
