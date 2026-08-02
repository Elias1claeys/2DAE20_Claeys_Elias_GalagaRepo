#include "Core/GameObject.h"
#include "Event/Subject.h"

namespace dae
{
	class Enemy : public Component, public Subject
	{

	public:
		
		Enemy(GameObject* owner, glm::vec2 formationPos, float yPosEnemie);
		virtual ~Enemy() = default;
		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

		void Update() override;
		void Notify(Event event, GameObject* gameObject);
		void SetEnemieTexture(glm::vec2 prevPos);
		void SetEnemieTexture(float x);
		glm::vec2 GetFormationPos() const { return m_FormationPos; }

	private:
		glm::vec2 m_FormationPos{};
		bool m_Flying{false};
		float m_SourceRectX{};
		float m_SourceRectY{};
		float m_Time{};
		float m_Size{};
	};
}