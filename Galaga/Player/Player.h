#include "Core/GameObject.h"
#include "Enemies/EnemiesController/EnemiesController.h"
#include "Event/Subject.h"

namespace dae
{
	class Player : public Component, public Subject
	{
	public:
		Player(GameObject* owner, EnemiesController* enemiesController);
		virtual ~Player() = default;
		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

		void Update() override;
		void SetDirection(const glm::vec2& direction);
		void Shoot();

	private:
		bool m_CanShoot = true;
		float m_Speed = 100.0f;
		float m_Time = 0.f;
		glm::vec2 m_Direction{ 0.0f, 0.0f };
		std::vector<std::unique_ptr<GameObject>> m_Bullets{};
		EnemiesController* m_EnemiesController{};
	};
}