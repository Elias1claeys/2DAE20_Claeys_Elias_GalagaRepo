#include "Dead.h"
#include "Components/Texture.h"
#include "Core/DeltaTime.h"

namespace dae
{
	Dead::Dead(GameObject* owner) : Component(owner) 
	{
		GetOwner()->AddComponent<Texture>()->SetTexture("Galaga2.png");
		GetOwner()->GetComponent<Texture>()->SetSourceRect(289.5f, 37.5f, 36.f, 36.f);

	}

	void Dead::Update() 
	{
		m_Time += Time::GetInstance().GetDeltaTime();

		if (m_Time > 1.f)
		{
			if (m_Index == 5)
			{
				GetOwner()->RemoveAllComponents();
			}
			else
			{
				m_Index++;
				GetOwner()->GetComponent<Texture>()->SetSourceRect(289.5f + m_Index * 36.f, 37.5f, 36.f, 36.f);
			}
		}
	}
}