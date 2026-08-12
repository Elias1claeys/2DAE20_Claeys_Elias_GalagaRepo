#include "Enemies/EnemyObserver.h"
#include "Enemies/EnemiesController/EnemiesController.h"
#include "GameEvents.h"
#include "StateMachine/State.h"

namespace dae
{
	EnemyObserver::EnemyObserver(EnemiesController* enemySpawner)
		: m_EnemySpawner(enemySpawner)
	{}

	void EnemyObserver::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == ENEMY_IN_FORMATION || event.id == ENEMY_HIT_BEFORE_FORMATION)
		{
			m_EnemySpawner->BackInFormationOrKilledTrying();
		}
	}
}