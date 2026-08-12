#include "CollisionObserver.h"
#include "Components/Transform.h"
#include "Event/Event.h"
#include "GameEvents.h"
#include "Enemies/EnemiesController/EnemiesController.h"
#include "Collider/Collider.h"
#include "Enemies/Enemy.h"
#include "StateMachine/State.h"
#include "Enemies/EnemyStates/EnemyState.h"
#include "Enemies/Path/BezierPath.h"
#include "Explosion/ExplosionAnimation.h"

namespace dae
{
	void Collision::OnNotify(GameObject* bullet, const Event& event)
	{
		if (event.id == ENEMY_HIT)
		{
			if (!event.args[0].go->HasComponent<Enemy>())
				return;

			if (!event.args[0].go->GetComponent<Enemy>()->IsEnemyKilled())
			{
				bullet->RemoveAllComponents();
				return;
			}

			if (auto stateComp = event.args[0].go->GetComponent<State>())
			{
				if (auto enemyState = dynamic_cast<EnemyState*>(stateComp->GetGameState()))
				{
					enemyState->EnemyHit();
				}
			}

			bullet->RemoveAllComponents();
			event.args[0].go->RemoveComponent<Enemy>();
			event.args[0].go->RemoveComponent<State>();
			event.args[0].go->RemoveComponent<BezierPath>();

			event.args[0].go->AddComponent<ExplosionAnimation>();
		}
	}
}