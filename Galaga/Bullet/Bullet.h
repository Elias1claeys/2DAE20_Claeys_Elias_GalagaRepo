#include "Core/GameObject.h"

namespace dae
{
	class Bullet : public Component
	{
	public:
		Bullet(GameObject* owner, glm::vec2 direction);
		virtual ~Bullet() = default;
		Bullet(const Bullet& other) = delete;
		Bullet(Bullet&& other) = delete;
		Bullet& operator=(const Bullet& other) = delete;
		Bullet& operator=(Bullet&& other) = delete;

		void Update() override;
		void SetDirection(glm::vec2 dir) { m_Direction = dir; }

	private:
		glm::vec2 m_Direction{ 0.0f, 0.0f };
		float m_SpeedY = 300.f;
		float m_SpeedX = 100.f;
	};
}