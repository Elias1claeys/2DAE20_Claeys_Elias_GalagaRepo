#include "Enemies/EnemyObserver.h"

#include "GameEvents.h"
#include "StateMachine/State.h"

namespace dae
{
	void EnemyObserver::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == ENEMY_IN_FORMATION)
		{
			m_EnemiesInFormation++;
		}
		if (event.id == ENEMY_OUT_FORMATION)
		{
			m_EnemiesInFormation--;
		}

		
	}
}