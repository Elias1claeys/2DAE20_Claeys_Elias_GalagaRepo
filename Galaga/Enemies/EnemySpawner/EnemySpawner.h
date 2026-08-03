#include "Core/GameObject.h"
#include "Enemies/EnemyObserver.h"

namespace dae
{
	class EnemySpawner : public Component
	{
	public:

		enum class EnemyType
		{
			Bee,
			Flie,
			Boss
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

		EnemySpawner(GameObject* owner);
		virtual ~EnemySpawner() = default;
		EnemySpawner(const EnemySpawner& other) = delete;
		EnemySpawner(EnemySpawner&& other) = delete;
		EnemySpawner& operator=(const EnemySpawner& other) = delete;
		EnemySpawner& operator=(EnemySpawner&& other) = delete;

		void Update() override;
		void AddWave(Wave wave);
		void EnemyBackInFormation();
		
	private:
		void SpawnEnemy(int waveIndex, int enemieIndex);

		std::vector<std::unique_ptr<GameObject>> m_Enemies;
		std::vector<Wave> m_Waves;
		float m_Time{ 1.f };
		int m_EnemyIndex{0};
		int m_WaveIndex{0};
		int m_EnemiesSpawned{ 0 };
		int m_EnemiesInFormation{ 0 };
	};
}