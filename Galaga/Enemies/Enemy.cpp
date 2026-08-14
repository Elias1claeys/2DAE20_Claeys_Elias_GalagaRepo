#include "Enemy.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include <glm/gtc/constants.hpp>
#include "Core/DeltaTime.h"
#include "GameEvents.h"
#include "Collider/Collider.h"
#include "Bullet/Bullet.h"

namespace dae
{
	Enemy::Enemy(GameObject* owner, glm::vec2 formationPos, float yPosEnmie, EnemyType type, GameObject* player)
		: Component(owner), m_FormationPos(formationPos), m_Type(type), m_Player(player)
	{
		m_Bullet = std::make_unique<GameObject>();
		m_Bullet->AddComponent<Bullet>(glm::vec2(0, 0));
		m_Bullet->GetComponent<Transform>()->SetLocalPosition(glm::vec2(-100, -100));
		m_Bullet->SetParent(GetOwner()->GetParent(), false);

		GetOwner()->AddComponent<Texture>();
		GetOwner()->GetComponent<Texture>()->SetTexture("Galaga2.png");

		m_SourceRectY = 1.5f + yPosEnmie;
		m_SourceRectX = 1.5f;
		m_Size = 15.f;

		GetOwner()->GetComponent<Texture>()->SetSize({ 30, 30 });
		GetOwner()->GetComponent<Texture>()->SetSourceRect(m_SourceRectX, m_SourceRectY, m_Size, m_Size);

		Event e{ PLAYER_HIT };
		m_Player->GetComponent<Collider>()->AddTrigger(Collider::Trigger{ GetOwner(), e, glm::vec2(30, 30), glm::vec2(0, 0), true });
		m_Player->GetComponent<Collider>()->AddTrigger(Collider::Trigger{ m_Bullet.get(), e, glm::vec2(30, 30), glm::vec2(0, 0), true});
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

	void Enemy::Shoot()
	{
		auto enemyPos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		m_Bullet->GetComponent<Transform>()->SetLocalPosition(glm::vec2(enemyPos.x, enemyPos.y - 50.f));
		
		float x = 1;

		if (m_Direction.x < 0)
			x = -1;

		m_Bullet->GetComponent<Bullet>()->SetDirection(glm::vec2(x, 1));
	}

	void Enemy::SetEnemieTexture(glm::vec2 prevPos)
	{
		glm::vec2 currentpos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		m_Direction = currentpos - prevPos;

		float angle = std::atan2(m_Direction.y, m_Direction.x);

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

	bool Enemy::IsBossKilled()
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