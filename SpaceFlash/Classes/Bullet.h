#pragma once
#include "cocos2d.h"
#include "Entity.h"

class CBullet : public CEntity
{
public: 
	enum Type {
		Normal = 0,
		Fast,
		Power,
		Rocket,
		HeroNormal,
	};

	static CBullet *create(bool isHero, cocos2d::Point const& position, Type type);

	void Update(float dt) override;
private:
	CBullet();
	void SetParams();
	void initOptions();
	void initExplosionAnim();

	Type m_type;
	cocos2d::RefPtr<cocos2d::Animate> m_explosion;

	int m_bitmask;
	int m_direction;
	int m_Speed;

};

