#include "EnemySpawner.h"
#include "Core/DeltaTime.h"
#include "Enemies/Types/Bee/Bee.h"
#include "Enemies/Types/Boss/Boss.h"
#include "Enemies/Types/Flie/Flie.h"
#include "Enemies/Enemy.h"
#include "Enemies/Path/BezierPath.h"
#include "StateMachine/State.h"
#include "Enemies/EnemyStates/FlyingToFormation.h"
#include "GameEvents.h"

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
			if(m_EnemyIndex != m_Waves[m_WaveIndex].enemies.size())
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

	void EnemySpawner::EnemyBackInFormation()
	{
		m_EnemiesInFormation++;

		if (m_EnemiesSpawned == m_EnemiesInFormation)
		{
			if (m_EnemiesSpawned != 40)
			{
				m_WaveIndex++;
				m_EnemyIndex = 0;
			}
		}
	}

	void EnemySpawner::SpawnEnemy(int waveIndex, int enemyIndex)
	{
		auto enemy = std::make_unique<GameObject>();
		auto currentWave = m_Waves[waveIndex];

		switch (currentWave.enemies[enemyIndex].type)
		{
			case EnemyType::Bee:
				enemy->AddComponent<Enemy>(currentWave.enemies[enemyIndex].endPoint, 18.f);
				break;
			case EnemyType::Flie:
				enemy->AddComponent<Enemy>(currentWave.enemies[enemyIndex].endPoint, 54.f);
				break;
			case EnemyType::Boss:
				enemy->AddComponent<Enemy>(currentWave.enemies[enemyIndex].endPoint, 90.f);
				break;
		}
		
		auto enemyObserver = std::make_unique<EnemyObserver>(this);
		enemy->GetComponent<Enemy>()->AddObserver(std::move(enemyObserver));

		Event event{ ENEMY_SPAWNED };
		enemy->GetComponent<Enemy>()->Notify(event);

		enemy->GetComponent<Transform>()->SetLocalPosition(currentWave.startPoint);
		enemy->AddComponent<BezierPath>();
		enemy->AddComponent<State>(std::make_unique<dae::FlyingToFormation>(nullptr, currentWave.curvePoint, currentWave.rotationPoint));
		enemy->SetParent(GetOwner(), false);

		m_Enemies.push_back(std::move(enemy));
		m_EnemiesSpawned++;
	}

	void EnemySpawner::AddWave(Wave wave)
	{
		m_Waves.push_back(wave);
	}
}