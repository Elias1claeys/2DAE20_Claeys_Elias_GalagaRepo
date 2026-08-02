#include "Enemies/EnemyObserver.h"

#include "GameEvents.h"

namespace dae
{
	EnemyObserver::EnemyObserver(GameObject* enemy)
		: m_pEnemy(enemy)
	{}

	void EnemyObserver::OnNotify(GameObject* , const Event& event)
	{
		if (event.id == ENEMY_BACK_INTO_FORMATION)
		{

		}
	}
}