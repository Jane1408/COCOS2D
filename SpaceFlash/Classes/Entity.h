#pragma once
#include "cocos2d.h"


class CEntity 
	: public cocos2d::Sprite
{
public: 
	CEntity();
	~CEntity();

	virtual void Update(float dt) = 0;

	void SetHealthPoint(float health);
	void SetDamage(float damage);
	float GetDamage();
	void Demaged(float damage);
	bool IsLife();
	void Destroy();
	void Kill();
	float GetHealth();
private:
	float m_health;
	float m_damage;
	bool m_isLife;

};

