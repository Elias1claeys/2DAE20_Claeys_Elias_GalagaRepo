#include "Bullet.h"
#include "Components/Transform.h"
#include "Components/Texture.h"
#include "Core/DeltaTime.h"

namespace dae
{
	Bullet::Bullet(GameObject* owner, glm::vec2 direction)
		: Component(owner)
		, m_Direction(direction)
	{
		GetOwner()->AddComponent<Texture>()->SetTexture("Galaga2.png");
		GetOwner()->GetComponent<Texture>()->SetSize({ 40, 40 });
		GetOwner()->GetComponent<Texture>()->SetSourceRect(307.5f, 154.5f, 15.f, 15.f);
		
	}

	void Bullet::Update()
	{
		auto pos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		pos += m_Direction * m_Speed * Time::GetInstance().GetDeltaTime();
		GetOwner()->GetComponent<Transform>()->SetLocalPosition(pos);
	}
}