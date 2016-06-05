#include "Entity.h"
#include "ui/CocosGUI.h" 
#include "Definitions.h"


CEntity::CEntity()
	: m_damage(0)
	, m_health(0)
	, m_isLife(true)
{
}


CEntity::~CEntity()
{
}

void CEntity::SetHealthPoint(float health)
{
	m_health = health;
}

void CEntity::SetDamage(float damage)
{
	m_damage = damage;
}

float CEntity::GetDamage()
{
	return m_damage;
}

void CEntity::Demaged(float damage)
{
	m_health -= damage;
	if (m_health <= 0 && m_isLife)
	{
		Kill();
	}
	cocos2d::EventCustom event(UPDATE_WAVE_HP);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

bool CEntity::IsLife()
{
	return m_isLife;
}

void CEntity::Destroy()
{
	this->removeFromParentAndCleanup(true);
}

void CEntity::Kill()
{

	this->getPhysicsBody()->setEnabled(false);

	if (m_deadAnim != nullptr && m_isLife)
	{
		runAction(m_deadAnim);

	}
	m_isLife = false;
}

float CEntity::GetHealth()
{
	return m_health;
}

void CEntity::SetdeadAnimate(cocos2d::Animate * anim)
{
	m_deadAnim = anim;
}

void CEntity::SetExtaraAnim(cocos2d::Animate * anim)
{
	m_extraAnim = anim;
}

cocos2d::RefPtr<cocos2d::Animate> CEntity::GetExtraAnim()
{
	return m_extraAnim;
}

bool CEntity::IsDeadDone()
{
	return m_deadAnim->isDone();
}
