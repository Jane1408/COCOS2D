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
	void SetdeadAnimate(cocos2d::Animate * anim);
	void SetExtaraAnim(cocos2d::Animate * anim);
	cocos2d::RefPtr<cocos2d::Animate> GetExtraAnim();
	bool IsDeadDone();
private:
	float m_health = 0;
	float m_damage = 0;
	bool m_isLife = false;
	cocos2d::RefPtr<cocos2d::Animate> m_deadAnim;
	cocos2d::RefPtr<cocos2d::Animate> m_extraAnim;

};

