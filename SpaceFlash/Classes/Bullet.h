#pragma once
#include "cocos2d.h"
#include "Entity.h"

class CBullet : public CEntity
{
public: 
	enum Type {
		Normal = 0,
		Fast,
		Power
	};

	static CBullet *create(bool isHero, cocos2d::Point const& position, Type type);

	void Update(float dt) override;
private:
	CBullet();
	void SetParams();
	void initOptions();
	Type m_type;

	int m_bitmask;
	int m_direction;
	int m_Speed;

};

