#include "BackGround.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Core/DeltaTime.h"

dae::BackGround::BackGround(GameObject* pOwner)
	: Component(pOwner)
{
	m_Background1 = std::make_unique<GameObject>();
	m_Background1->AddComponent<Texture>()->SetTexture("Background.png");
	m_Background1->GetComponent<Texture>()->SetSize(glm::vec2(512, 512));

	m_Background2 = std::make_unique<GameObject>();
	m_Background2->AddComponent<Texture>()->SetTexture("Background.png");
	m_Background2->GetComponent<Texture>()->SetSize(glm::vec2(512, 512));
	m_Background2->GetComponent<Transform>()->SetLocalPosition(glm::vec3(0, -512, 0));

	m_Background1->SetParent(GetOwner(), false);
	m_Background2->SetParent(GetOwner(), false);
}

void dae::BackGround::Update()
{
	auto pos1 = m_Background1->GetComponent<Transform>()->GetWorldPosition();
	auto pos2 = m_Background2->GetComponent<Transform>()->GetWorldPosition();

	pos1.y += m_speed * Time::GetInstance().GetDeltaTime();
	pos2.y += m_speed * Time::GetInstance().GetDeltaTime();

	if (pos2.y >= 0)
	{
		pos1.y = 0;
		pos2.y = -512;
	}

	m_Background1->GetComponent<Transform>()->SetLocalPosition(pos1);
	m_Background2->GetComponent<Transform>()->SetLocalPosition(pos2);
}