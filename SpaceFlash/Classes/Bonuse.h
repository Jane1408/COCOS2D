#pragma once
#include "cocos2d.h"
#include "Entity.h"

class CBonuce : public CEntity
{
public: 
	enum Type {
		Health = 0,
		Shield,
		Power,
		Bomb,
	};

	static CBonuce *create(cocos2d::Point const& position);

	void Update(float dt) override;
private:
	CBonuce();
	void initOptions();
	Type m_type;

	int m_bitmask;
	int m_direction = -1;
	int m_Speed = 3;

};

