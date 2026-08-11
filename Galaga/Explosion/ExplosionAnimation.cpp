#include "ExplosionAnimation.h"
#include "Components/Texture.h"
#include "Core/DeltaTime.h"

namespace dae
{
	ExplosionAnimation::ExplosionAnimation(GameObject* owner) : Component(owner) 
	{
		
	}

	void ExplosionAnimation::Update() 
	{
		m_Time += Time::GetInstance().GetDeltaTime();
		
		if (m_Time > 0.1f)
		{
			if (m_Index == 4)
			{
				GetOwner()->RemoveAllComponents();
			}
			else
			{
				GetOwner()->GetComponent<Texture>()->SetSize({ 50.f, 50.f });
				GetOwner()->GetComponent<Texture>()->SetSourceRect(289.5f + m_Index * 34.f, 1.5f, 31.f, 31.f);
				m_Index++;
				m_Time = 0;
			}
		}
	}
}