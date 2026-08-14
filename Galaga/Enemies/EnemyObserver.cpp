#include "Enemies/EnemyObserver.h"
#include "Enemies/EnemiesController/EnemiesController.h"
#include "GameEvents.h"
#include "StateMachine/State.h"

namespace dae
{
	EnemyObserver::EnemyObserver(EnemiesController* enemySpawner, Player* player)
		: m_EnemySpawner(enemySpawner), m_Player(player)
	{}

	void EnemyObserver::OnNotify(GameObject* gameObject, const Event& event)
	{
		if (event.id == ENEMY_IN_FORMATION || event.id == ENEMY_HIT_BEFORE_FORMATION)
		{
			m_EnemySpawner->BackInFormationOrKilledTrying();
		}
		if (event.id == PLAYER_IN_BEAM)
		{
			m_Player->StuckInBeam(event.args[0].v2);
			m_Player->Notify(event, gameObject);
		}
		if (event.id == BEAM_SHOT || event.id == POINTS_GAINED)
		{
			m_Player->Notify(event, gameObject);
		}
	}
}