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

	private:
		glm::vec2 m_Direction{ 0.0f, 0.0f };
		float m_Speed = 300.f;
	};
}