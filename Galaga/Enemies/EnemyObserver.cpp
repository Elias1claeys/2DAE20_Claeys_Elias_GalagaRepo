#include "Enemies/EnemyObserver.h"
#include "Enemies/EnemySpawner/EnemySpawner.h"
#include "GameEvents.h"
#include "StateMachine/State.h"

namespace dae
{
	EnemyObserver::EnemyObserver(EnemySpawner* enemySpawner)
		: m_EnemySpawner(enemySpawner)
	{}

	void EnemyObserver::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == ENEMY_IN_FORMATION)
		{
			m_EnemySpawner->CheckForNextWave();
		}
	}
}