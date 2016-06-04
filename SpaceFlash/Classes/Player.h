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
private:
	Player();
	bool m_isShooting;
	void Shoot(float dt);
	void initOptions();
	cocos2d::Vec2 m_shootPosition;
	cocos2d::Sprite * m_healthLine;
};

