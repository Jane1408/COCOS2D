#include "ui/CocosGUI.h" 
#include "WaveCommander.h"
#include "Definitions.h"
WaveCommander::WaveCommander()
{
}

WaveCommander * WaveCommander::create(cocos2d::Layer * layer)
{
	WaveCommander * waveCom = new WaveCommander();
	waveCom->m_layer = layer;
	waveCom->SetProgressLine();
	return waveCom;
}

WaveCommander::~WaveCommander()
{
}

void WaveCommander::StartWave()
{
		std::vector<CEnemy::Type> waveEnemyes;
		switch (wave)
		{
		case 1: waveEnemyes = WAVE1; break;
		case 2: waveEnemyes = WAVE2; break;
		case 3: waveEnemyes = WAVE3; break;
		case 4: waveEnemyes = WAVE4; break;
		case 5: waveEnemyes = BOSS1; break;
		case 6: waveEnemyes = WAVE6; break;
		case 7: waveEnemyes = WAVE7; break;
		case 8: waveEnemyes = WAVE8; break;
		case 9: waveEnemyes = WAVE9; break;
		case 10: waveEnemyes = BOSS2; break;
		case 11: waveEnemyes = WAVE11; break;
		case 12: waveEnemyes = WAVE12; break;
		case 13: waveEnemyes = WAVE13; break;
		case 14: waveEnemyes = WAVE14; break;
		case 15: waveEnemyes = BOSS3; break;

		}
		SetEnemyes(waveEnemyes);
}

void WaveCommander::Update(float dt)
{
	for (auto it = m_enemyes.begin(); it != m_enemyes.end();)
	{
		if (!(*it)->IsLife())
		{
			m_enemyes.erase(it);
		}
		else
		{
			++it;
		}
	}
	if (m_enemyes.size() == 0)
	{
		m_waveHealth = 0;
		StartWave();
		++wave;
		UpdateProgressLine();
		if (wave > 16)
		{
			cocos2d::EventCustom event(WIN_GAME);
			cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		}
	}
}

void WaveCommander::KillAll()
{
	for (auto &it : m_enemyes)
	{
		it->Kill();
	}
}

void WaveCommander::SetProgressLine()
{
	m_progressLine = new cocos2d::Sprite();
	m_progressLine->initWithFile(PROGRESS_LINE);
	m_progressLine->setPosition({ m_layer->getContentSize().width / 2, m_layer->getContentSize().height - m_progressLine->getContentSize().height / 2 });
	m_layer->addChild(m_progressLine);
}

void WaveCommander::UpdateProgressLine()
{
	int currentHealth = 0;
	for (auto *it : m_enemyes)
	{
		currentHealth += it->GetHealth();
	}
	currentHealth = currentHealth < 0 ? 0 : currentHealth;
	m_progressLine->setScaleX(float(currentHealth) / float(m_waveHealth));
}

int WaveCommander::GetWaveNumber()
{
	return wave - 1;
}

void WaveCommander::SetEnemyes(std::vector<CEnemy::Type> const& waveEnemyes)
{
	for (auto &it : waveEnemyes)
	{
		int pos = cocos2d::RandomHelper::random_int(100, int(m_layer->getContentSize().width - 100));
		auto enemy = CEnemy::create({ float(pos), m_layer->getContentSize().height - 100 }, it);
		m_waveHealth += enemy->GetHealth();
		m_layer->addChild(enemy);
		m_enemyes.push_back(enemy);
	}
}
