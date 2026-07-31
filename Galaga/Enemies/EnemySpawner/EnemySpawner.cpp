#include "EnemySpawner.h"
#include "Core/DeltaTime.h"
#include "Enemies/Bee/Bee.h"
#include "Enemies/Boss/Boss.h"
#include "Enemies/Flie/Flie.h"
#include "Enemies/Path/BezierPath.h"

namespace dae
{
	EnemySpawner::EnemySpawner(GameObject* Owner) :
		Component(Owner)
	{
	}

	void EnemySpawner::Update()
	{
		m_Time += Time::GetInstance().GetDeltaTime();

		if (m_Time > 0.1f)
		{
			if (m_EnemyIndex == m_Waves[m_WaveIndex].enemies.size())
			{
				
			}
			else
			{
				SpawnEnemy(m_WaveIndex, m_EnemyIndex);

				if (m_Waves[m_WaveIndex].enemies.size() == 4)
				{
					SpawnEnemy(m_WaveIndex + 1, m_EnemyIndex);
				}

				m_EnemyIndex++;
			}

			m_Time = 0.f;
		}
	}

	void EnemySpawner::SpawnEnemy(int waveIndex, int enemyIndex)
	{
		auto enemy = std::make_unique<GameObject>();
		auto currentWave = m_Waves[waveIndex];

		switch (currentWave.enemies[enemyIndex].type)
		{
			case EnemyType::Bee:
				enemy->AddComponent<Bee>();
				break;
			case EnemyType::Flie:
				enemy->AddComponent<Flie>();
				break;
			case EnemyType::Boss:
				enemy->AddComponent<Boss>();
				break;
		}

		BezierPath::BezierSegment bezierSegment{currentWave.startPoint, currentWave.enemies[enemyIndex].endPoint, currentWave.curvePoint};
		enemy->AddComponent<BezierPath>(bezierSegment, currentWave.rotationPoint);
		enemy->SetParent(GetOwner(), false);

		m_Enemies.push_back(std::move(enemy));
	}

	void EnemySpawner::AddWave(Wave wave)
	{
		m_Waves.push_back(wave);
	}
}