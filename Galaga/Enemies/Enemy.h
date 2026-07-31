#include "Core/GameObject.h"

namespace dae
{
	class Enemy : public Component
	{

	public:
		Enemy(GameObject* owner, float yPosEnemie);
		virtual ~Enemy() = default;
		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

		void Update() override;
		void SetEnemieTexture(glm::vec2 prevPos);
		void SetEnemieTexture(float x);

	private:
		bool m_Flying{false};
		float m_SourceRectX{};
		float m_SourceRectY{};
		float m_Time{};
		float m_Size{};
	};
}