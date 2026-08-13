#include "HealthDisplay.h"
#include "Components/Transform.h"
#include "Components/Texture.h"
#include "Resources/ResourceManager.h"

namespace dae
{
	HealthDisplay::HealthDisplay(GameObject* owner)
		: Component(owner)
	{
		for (int i = 0; i < 3; i++)
		{
			auto health = std::make_unique<GameObject>();
			health->AddComponent<Texture>()->SetTexture("Galaga2.png");
			health->GetComponent<Texture>()->SetSize({ 25.f, 25.f });
			health->GetComponent<Texture>()->SetSourceRect(109.5f, 1.5f, 15.f, 15.f);
			health->GetComponent<Transform>()->SetLocalPosition({ 0.f + 30.f * i, 482.f });
			health->SetParent(GetOwner(), false);
			m_HealthDisplay.push_back(std::move(health));
		}
	}

	void HealthDisplay::DoDamage()
	{
		m_HealthDisplay.erase(m_HealthDisplay.end() - 1);
	}
}

