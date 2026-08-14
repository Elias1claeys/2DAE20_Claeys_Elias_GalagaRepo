#include "EnemiesController.h"
#include "Core/DeltaTime.h"
#include "Enemies/Enemy.h"
#include "Enemies/Path/BezierPath.h"
#include "StateMachine/State.h"
#include "Enemies/EnemyStates/Flying.h"
#include "GameEvents.h"
#include "Components/Texture.h"
#include "Collider/Collider.h"

namespace dae
{
	EnemiesController::EnemiesController(GameObject* Owner) :
		Component(Owner)
	{
		m_EnemiesParent = std::make_unique<GameObject>();
		m_EnemiesParent->SetParent(GetOwner(), false);
	}

	void EnemiesController::Update()
	{
		if (!m_AllEnemiesSpawned)
		{
			SpawnWave();
		}
		else
		{
			MoveInFormation();
		}
	}

	void EnemiesController::SpawnWave()
	{
		m_Time += Time::GetInstance().GetDeltaTime();

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

	void EnemiesController::MoveInFormation()
	{
		for (auto& enemy : m_EnemiesParent->GetChildren())
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

		for (auto& enemy : m_EnemiesParent->GetChildren())
		{
			if (!enemy->HasComponent<Enemy>())
				continue;

			glm::vec2 moveDir = m_Direction * m_Speed * Time::GetInstance().GetDeltaTime();
			enemy->GetComponent<Enemy>()->AddToFormationPos(moveDir);
		}
	}

	void EnemiesController::BackInFormationOrKilledTrying()
	{
		m_RemainingEnemies--;

		if (m_RemainingEnemies == 0)
		{
			if (!m_AllEnemiesSpawned)
			{
				CheckForNextWave();
			}
			else
			{
				PickEnemiesForAttack();
			}
		}
	}

	void EnemiesController::CheckForNextWave()
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
			PickEnemiesForAttack();
		}
	}

	void EnemiesController::PickEnemiesForAttack()
	{
		std::vector<GameObject*> bees;
		std::vector<GameObject*> flies;
		std::vector<GameObject*> bosses;

		for (auto& enemy : m_EnemiesParent->GetChildren())
		{
			if (!enemy->HasComponent<Enemy>())
				continue;
			else if (enemy->GetComponent<Enemy>()->IsDead())
				continue;

			auto enemyComponent = enemy->GetComponent<Enemy>();

			switch (enemyComponent->GetType())
			{
			case EnemyType::Bee:
				bees.push_back(enemy);
				break;

			case EnemyType::Flie:
				flies.push_back(enemy);
				break;

			case EnemyType::Boss:
				bosses.push_back(enemy);
				break;
			}
		}

		int r = rand() % 3 + 1;
		ChooseAttack(bees, flies, bosses, r);
	}

	void EnemiesController::ChooseAttack(std::vector<GameObject*> bees, std::vector<GameObject*> flies, std::vector<GameObject*> bosses, int attack)
	{
		if (bees.empty() && flies.empty() && bosses.empty())
			return;

		int randomBee = 0;
		int randomFlie = 0;
		int randomBoss = 0;

		if(!bees.empty())
			randomBee = rand() % bees.size();

		if (!flies.empty())
			randomFlie = rand() % flies.size();

		if(!bosses.empty())
			randomBoss = rand() % bosses.size();

		switch (attack)
		{
		case 1:
			if (bosses.empty())
				ChooseAttack(bees, flies, bosses, 2);
			else
			{
				bosses[randomBoss]->GetComponent<Enemy>()->SetBeamAttack(true);
				bosses[randomBoss]->GetComponent<State>()->GoToNextStage();
				m_RemainingEnemies = 1;
			}
			break;

		case 2:
			if (bosses.empty() && flies.empty())
				ChooseAttack(bees, flies, bosses, 3);
			else
			{
				if (!bosses.empty())
				{
					bosses[randomBoss]->GetComponent<Enemy>()->SetBeamAttack(false);
					bosses[randomBoss]->GetComponent<State>()->GoToNextStage();
					m_RemainingEnemies++;
				}
					

				if (!flies.empty())
				{
					flies[randomFlie]->GetComponent<State>()->GoToNextStage();
					m_RemainingEnemies++;

					if (flies.size() >= 2)
					{
						int secondFlie = rand() % flies.size();

						while (randomFlie == secondFlie)
							secondFlie = rand() % flies.size();

						flies[secondFlie]->GetComponent<State>()->GoToNextStage();
						m_RemainingEnemies++;
					}
						
				}
			}
			break;

		case 3:
			if (bees.empty() && flies.empty())
				ChooseAttack(bees, flies, bosses, 1);
			else
			{
				if (!bees.empty())
				{
					bees[randomBee]->GetComponent<State>()->GoToNextStage();
					m_RemainingEnemies++;
				}
					
				if (!flies.empty())
				{
					flies[randomFlie]->GetComponent<State>()->GoToNextStage();
					m_RemainingEnemies++;
				}
			}
			break;
		}
	}

	void EnemiesController::SpawnEnemy(int waveIndex, int enemyIndex)
	{
		auto enemy = std::make_unique<GameObject>();
		auto currentWave = m_Waves[waveIndex];

		switch (currentWave.enemies[enemyIndex].type)
		{
			case EnemyType::Bee:
				enemy->AddComponent<Enemy>(currentWave.enemies[enemyIndex].endPoint, 18.f, EnemyType::Bee, m_Player);
				break;
			case EnemyType::Flie:
				enemy->AddComponent<Enemy>(currentWave.enemies[enemyIndex].endPoint, 54.f, EnemyType::Flie, m_Player);
				break;
			case EnemyType::Boss:
				enemy->AddComponent<Enemy>(currentWave.enemies[enemyIndex].endPoint, 90.f, EnemyType::Boss, m_Player);
				break;
		}
		
		auto enemyObserver = std::make_unique<EnemyObserver>(this);
		enemy->GetComponent<Enemy>()->AddObserver(std::move(enemyObserver));

		Event event{ ENEMY_SPAWNED };
		enemy->GetComponent<Enemy>()->Notify(event);

		enemy->GetComponent<Transform>()->SetLocalPosition(currentWave.startPoint);
		enemy->AddComponent<BezierPath>();
		enemy->AddComponent<State>(std::make_unique<dae::Flying>(nullptr, currentWave.curvePoint, glm::vec2{256, 256}, currentWave.rotationPoint));
		enemy->SetParent(m_EnemiesParent.get(), false);

		m_Enemies.push_back(std::move(enemy));
	}

	void EnemiesController::AddWave(Wave wave)
	{
		m_Waves.push_back(wave);
	}

	void EnemiesController::AddEnemyCollisions(GameObject* object, Event event)
	{
		object->GetComponent<Collider>()->ResetAllTriggers();

		
		for (auto& enemy : m_EnemiesParent->GetChildren())
		{
			if (!enemy->GetComponent<Enemy>())
				continue;

			event.args[1].go = enemy;
			auto enemySize = enemy->GetComponent<Texture>()->GetSize();

			object->GetComponent<Collider>()->AddTrigger(Collider::Trigger{enemy, event, enemySize, {0.f, 0.f}, false});
		}
	}

	void EnemiesController::ResetAllEnemies()
	{
		m_EnemiesParent->RemoveAllChilderen();
		//m_Enemies.clear();
		m_Waves.clear();
		m_Time = 1.f;
		m_EnemyIndex = 0;
		m_WaveIndex = 0;
		m_RemainingEnemies = 8;
		m_AllEnemiesSpawned = false;
		m_Direction = { -1, 0 };

	}
}