#include "Beam.h"
#include "Components/Texture.h"
#include "Components/TransForm.h"
#include "Core/DeltaTime.h"

namespace dae
{
	Beam::Beam(GameObject* owner)
		: Component(owner)
	{
		GetOwner()->AddComponent<Texture>()->SetTexture("TractorBeam.png");
		GetOwner()->GetComponent<Texture>()->SetSourceRect(1.5f, 1.5f, 47, 79);
		GetOwner()->GetComponent<Texture>()->SetSize({ 40.f, 100.f });

		auto currentPos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		GetOwner()->GetComponent<Transform>()->SetLocalPosition({ currentPos.x - 5, currentPos.y + 20.f });
	}

	void Beam::Update()
	{
		if (m_Index <= 10)
		{
			m_Time += Time::GetInstance().GetDeltaTime();

			if (m_Time > 0.5f)
			{
				float currentAct = m_Index;

				if (m_Index > 5)
					currentAct = 10 - m_Index;

				GetOwner()->GetComponent<Texture>()->SetSourceRect(1.5f, 1.5f + (82.f * currentAct), 47.f, 79.f);
				m_Index++;
				m_Time = 0;
			}
		}
		else
		{
			GetOwner()->RemoveAllComponents();
		}
	}
}