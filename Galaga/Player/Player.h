#include "Core/GameObject.h"

namespace dae
{
	class Player : public Component
	{
	public:
		Player(GameObject* owner);
		virtual ~Player() = default;
		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

		void Update() override;
		void SetDirection(const glm::vec2& direction);
		void Shoot();

	private:
		float m_Speed = 200.0f;
		glm::vec2 m_Direction{ 0.0f, 0.0f };
		std::vector<std::unique_ptr<GameObject>> m_Bullets{};
	};
}