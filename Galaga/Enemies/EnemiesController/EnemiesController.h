#pragma once

#include "Core/GameObject.h"
#include "Enemies/EnemyObserver.h"
#include "Enemies/EnemyTypes.h"

namespace dae
{
	class EnemiesController : public Component
	{
	public:

		enum class Attacks
		{
			BossCapture,
			BossDive,
			BeeAttack
		};

		struct EnemyInfo
		{
			EnemyType type;
			glm::vec2 endPoint;
		};

		struct Wave
		{
			std::vector<EnemyInfo> enemies;
			glm::vec2 startPoint;
			glm::vec2 curvePoint;
			float rotationPoint = 0.f;
		};

		EnemiesController(GameObject* owner);
		virtual ~EnemiesController() = default;
		EnemiesController(const EnemiesController& other) = delete;
		EnemiesController(EnemiesController&& other) = delete;
		EnemiesController& operator=(const EnemiesController& other) = delete;
		EnemiesController& operator=(EnemiesController&& other) = delete;

		void Update() override;
		void AddWave(Wave wave);
		void BackInFormationOrKilledTrying();
		void AddEnemyCollisions(GameObject* object, Event event);
		void EnemyKilled();
		void GetPlayer(GameObject* player) { m_Player = player; }
		void ResetAllEnemies();
		
	private:
		void SpawnEnemy(int waveIndex, int enemieIndex);
		void MoveInFormation();
		void SpawnWave();
		void CheckForNextWave();
		void PickEnemiesForAttack();
		void ChooseAttack(std::vector<GameObject*> bees, std::vector<GameObject*> flies, std::vector<GameObject*> bosses, int attack);

		GameObject* m_Player{};
		std::vector<std::unique_ptr<GameObject>> m_Enemies;
		std::vector<Wave> m_Waves;
		float m_Time{ 1.f };
		int m_EnemyIndex{0};
		int m_WaveIndex{0};
		int m_RemainingEnemies{ 8 };
		bool m_AllEnemiesSpawned{ false };
		glm::vec2 m_Direction{ -1, 0 };
		float m_Speed = 50.f;
	};
}