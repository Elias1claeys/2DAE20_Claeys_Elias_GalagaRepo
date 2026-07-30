#include "Enemy.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include <glm/gtc/constants.hpp>

namespace dae
{
	Enemy::Enemy(GameObject* owner, float yPosEnmie)
		: Component(owner)
	{
		GetOwner()->AddComponent<Texture>();
		GetOwner()->GetComponent<Texture>()->SetTexture("Galaga2.png");

		m_SourceRectY = 1.5f + yPosEnmie;
		float x = 1.5f;
		float size = 15.f;

		GetOwner()->GetComponent<Texture>()->SetSize({ 40, 40 });
		GetOwner()->GetComponent<Texture>()->SetSourceRect(x, m_SourceRectY, size, size);
	}

	void Enemy::Update()
	{}

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

		float x = 1.5f + 18.f * index;
		GetOwner()->GetComponent<Texture>()->SetSourceRect(x, m_SourceRectY, 15.f, 15.f);
	}

	void Enemy::SetEnemieTexture(float x)
	{
		GetOwner()->GetComponent<Texture>()->SetSourceRect(x, m_SourceRectY, 15.f, 15.f);
	}
}