#include "HealthObserver.h"
#include "GameEvents.h"
#include "Player/Player.h"
#include "Components/Transform.h"

namespace dae
{
	HealthObserver::HealthObserver(HealthDisplay* health)
		: m_HealthDisplay(health)
	{
	}

	void HealthObserver::OnNotify(GameObject* gameObject, const Event& event)
	{
		if (event.id == PLAYER_HIT)
		{
			m_Health--;
			
			if (m_Health == 0)
			{
				Event e{ PLAYER_DIED };
				gameObject->GetComponent<Player>()->Notify(e, gameObject);
			}
			else
			{
				m_HealthDisplay->DoDamage();

				auto playerPos = gameObject->GetComponent<Transform>()->GetWorldPosition();

				float newPlayerPosX = 0.f;

				if (playerPos.x < 256.f)
					newPlayerPosX = 462.f;
				else
					newPlayerPosX = 0.f;

				gameObject->GetComponent<Transform>()->SetLocalPosition({ newPlayerPosX, 442.f});
			}
		}
	}
}