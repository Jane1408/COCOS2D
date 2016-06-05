#pragma once
#include "cocos2d.h" 
#include "Entity.h"
#include <vector>
#include <map>

class Player : public CEntity
{
public:
	static Player * create();
	void Update(float dt) override;
	void StartShooting();
	void StopShooting();
	void UpdateVisualHeals();
	void SetVisualHealth();
	void AddHealth();

	void StartDoubleShooting();
	void StopDoubleShooting(float dt);

	void StartImmortal();
	void StopImmortal(float dt);

	bool IsImmortal();
private:
	Player();
	bool m_isShooting;
	void Shoot(float dt);
	void initOptions();
	void initExplosionAnim();
	bool m_isDoubleShooting;
	bool m_isImmortal;

	cocos2d::RefPtr<cocos2d::Animate> m_explosion;
	cocos2d::RefPtr<cocos2d::Sprite> m_activeShield;

	cocos2d::Vec2 m_shootPosition;
	cocos2d::Sprite * m_healthLine;
};

