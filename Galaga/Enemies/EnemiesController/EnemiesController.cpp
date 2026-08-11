#include "EnemiesController.h"
#include "Core/DeltaTime.h"
#include "Enemies/Types/Bee/Bee.h"
#include "Enemies/Types/Boss/Boss.h"
#include "Enemies/Types/Flie/Flie.h"
#include "Enemies/Enemy.h"
#include "Enemies/Path/BezierPath.h"
#include "StateMachine/State.h"
#include "Enemies/EnemyStates/FlyingToFormation.h"
#include "GameEvents.h"
#include "Components/Texture.h"
#include "Collider/Collider.h"

namespace dae
{
	EnemiesController::EnemiesController(GameObject* Owner) :
		Component(Owner)
	{
		
	}

	void EnemiesController::Update()
	{
		m_Time += Time::GetInstance().GetDeltaTime();

		if (!m_AllEnemiesSpawned)
		{
			if (m_Time > 0.2f)
			{
				if (m_EnemyIndex != m_Waves[m_WaveIndex].enemies.size())
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
		else
		{
			for (auto& enemy : m_Enemies)
			{
				if (!enemy->HasComponent<Enemy>())
					continue;

				glm::vec2 currentPos = enemy->GetComponent<Enemy>()->GetFormationPos();
				
				if (currentPos.x < 0 || currentPos.x > 482)
				{
					m_Direction.x *= -1;
					break;
				}
			}

			for (auto& enemy : m_Enemies)
			{
				if (!enemy->HasComponent<Enemy>())
					continue;

				glm::vec2 moveDir = m_Direction * m_Speed * Time::GetInstance().GetDeltaTime();
				enemy->GetComponent<Enemy>()->AddToFormationPos(moveDir);
			}
		}
	}

	void EnemiesController::CheckForNextWave()
	{
		m_RemainingEnemies--;

		if (m_RemainingEnemies == 0)
		{
			if (m_WaveIndex < m_Waves.size() - 1)
			{
				if (m_Waves[m_WaveIndex].enemies.size() == 4)
					m_WaveIndex++;

				m_WaveIndex++;
				m_EnemyIndex = 0;
				m_RemainingEnemies = 8;
			}
			else
			{
				m_AllEnemiesSpawned = true;
			}
		}
	}

	void EnemiesController::SpawnEnemy(int waveIndex, int enemyIndex)
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
	}

	void EnemiesController::AddWave(Wave wave)
	{
		m_Waves.push_back(wave);
	}

	void EnemiesController::AddEnemyCollisions(GameObject* object, Event event)
	{
		for (auto& enemy : m_Enemies)
		{
			if (!enemy->GetComponent<Enemy>())
				continue;

			event.args[0].go = enemy.get();
			auto enemySize = enemy->GetComponent<Texture>()->GetSize();

			object->GetComponent<Collider>()->AddTrigger(Collider::Trigger{enemy.get(), event, enemySize, {0.f, 0.f}, false});
		}
	}
}