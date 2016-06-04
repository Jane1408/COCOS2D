#pragma once
#include "cocos2d.h"
#include "Enemy.h"
#include <vector>

const std::vector<CEnemy::Type> WAVE1 = {CEnemy::Common, CEnemy::Common, CEnemy::Common};
const std::vector<CEnemy::Type> WAVE2 = { CEnemy::Common, CEnemy::Common, CEnemy::HeavyCommon };
const std::vector<CEnemy::Type> WAVE3 = { CEnemy::HeavyCommon, CEnemy::HeavyCommon, CEnemy::HeavyCommon };
const std::vector<CEnemy::Type> WAVE4 = { CEnemy::HeavyCommon, CEnemy::HeavyCommon, CEnemy::DoubleCommon, CEnemy::DoubleCommon };
const std::vector<CEnemy::Type> BOSS1 = { CEnemy::FIRST_BOSS };
const std::vector<CEnemy::Type> WAVE6 = { CEnemy::HeavyCommon, CEnemy::HeavyCommon, CEnemy::DoubleCommon, CEnemy::DoubleCommon };
const std::vector<CEnemy::Type> WAVE7 = { CEnemy::HeavyCommon, CEnemy::DoubleCommon, CEnemy::FastDouble};
const std::vector<CEnemy::Type> WAVE8 = { CEnemy::DoubleCommon, CEnemy::DoubleCommon, CEnemy::DoubleCommon, CEnemy::FastDouble };
const std::vector<CEnemy::Type> WAVE9 = { CEnemy::DoubleCommon, CEnemy::DoubleCommon, CEnemy::FastDouble, CEnemy::FastDouble };
const std::vector<CEnemy::Type> BOSS2 = { CEnemy::SECOND_BOSS };
const std::vector<CEnemy::Type> WAVE11 = { CEnemy::FastDouble, CEnemy::FastDouble, CEnemy::Common, CEnemy::PowerDouble };
const std::vector<CEnemy::Type> WAVE12 = { CEnemy::PowerDouble, CEnemy::PowerDouble, CEnemy::PowerDouble, CEnemy::VeryHeavy };
const std::vector<CEnemy::Type> WAVE13 = { CEnemy::PowerDouble, CEnemy::PowerDouble, CEnemy::VeryHeavy, CEnemy::VeryHeavy };
const std::vector<CEnemy::Type> WAVE14 = { CEnemy::VeryHeavy, CEnemy::VeryHeavy, CEnemy::VeryHeavy, CEnemy::PowerDouble };
const std::vector<CEnemy::Type> BOSS3 = { CEnemy::THIRD_BOSS };





class WaveCommander
{
public: 
	static WaveCommander * create(cocos2d::Layer * layer);

	~WaveCommander();
	void StartWave();
	void Update(float dt);
private:
	WaveCommander();
	void SetEnemyes(std::vector<CEnemy::Type> const& waveEnemyes);

	cocos2d::Layer * m_layer;
	std::vector<CEntity*> m_enemyes;
	int wave = 1;
};

