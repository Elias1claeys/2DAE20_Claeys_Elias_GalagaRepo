#include "Enemy.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include <glm/gtc/constants.hpp>
#include "Core/DeltaTime.h"

namespace dae
{
	Enemy::Enemy(GameObject* owner, glm::vec2 formationPos, float yPosEnmie, EnemyType type, GameObject* player)
		: Component(owner), m_FormationPos(formationPos), m_Type(type), m_Player(player)
	{
		GetOwner()->AddComponent<Texture>();
		GetOwner()->GetComponent<Texture>()->SetTexture("Galaga2.png");

		m_SourceRectY = 1.5f + yPosEnmie;
		m_SourceRectX = 1.5f;
		m_Size = 15.f;

		GetOwner()->GetComponent<Texture>()->SetSize({ 30, 30 });
		GetOwner()->GetComponent<Texture>()->SetSourceRect(m_SourceRectX, m_SourceRectY, m_Size, m_Size);
	}

	void Enemy::Update()
	{
		m_Time += Time::GetInstance().GetDeltaTime();

		if (m_Time >= 0.5f)
		{
			if (!m_Flying)
			{
				m_SourceRectY += 18;
			}
			else
			{
				m_SourceRectY -= 18;
			}
			
			m_Flying = !m_Flying;
			m_Time = 0.f;
		}

		GetOwner()->GetComponent<Texture>()->SetSourceRect(m_SourceRectX, m_SourceRectY, m_Size, m_Size);
	}

	void Enemy::SetEnemieTexture(glm::vec2 prevPos)
	{
		glm::vec2 currentpos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		glm::vec2 dir = currentpos - prevPos;

		float angle = std::atan2(dir.y, dir.x);

		// Normalize to [0, 2pi)
		constexpr float twoPi = 2.0f * glm::pi<float>();
		if (angle < 0.f) angle += twoPi;

		constexpr int textureCount = 16;
		constexpr float sliceSize = twoPi / textureCount;

		int index = static_cast<int>((angle + sliceSize * 0.5f) / sliceSize) + 180 % textureCount;

		if (index > 15)
			index -= 15;

		m_SourceRectX = 1.5f + 18.f * index;
	}

	void Enemy::SetEnemieTexture(float x)
	{
		m_SourceRectX = x;
	}

	void Enemy::AddToFormationPos(glm::vec2 pos)
	{
		m_FormationPos += pos;
	}

	void Enemy::Notify(Event event)
	{
		Subject::Notify(event, GetOwner());
	}

	bool Enemy::IsEnemyKilled()
	{
		if (m_Type == EnemyType::Boss && !m_ShotOnce)
		{
			m_SourceRectY += 36.f;
			m_ShotOnce = true;
			return false;
		}
		
		return true;
	}
}