#include "Entity.h"
#include "ui/CocosGUI.h" 



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
	if (m_health <= 0)
	{
		m_isLife = false;
	}
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
	m_isLife = false;
}

float CEntity::GetHealth()
{
	return m_health;
}
