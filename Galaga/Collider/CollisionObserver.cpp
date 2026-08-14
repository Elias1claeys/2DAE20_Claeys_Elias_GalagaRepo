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
	void Collision::OnNotify(GameObject* gameObject, const Event& event)
	{
		if (event.id == ENEMY_HIT)
		{
			if (!event.args[1].go->HasComponent<Enemy>())
				return;

			if (!event.args[1].go->GetComponent<Enemy>()->IsBossKilled())
			{
				gameObject->GetComponent<Transform>()->SetLocalPosition({ -100, 0 });
				return;
			}

			if (auto stateComp = event.args[1].go->GetComponent<State>())
			{
				if (auto enemyState = dynamic_cast<EnemyState*>(stateComp->GetGameState()))
				{
					event.args[1].go->GetComponent<Enemy>()->EnemyDied();
					enemyState->EnemyHit();

					if (event.args[1].go->GetComponent<Enemy>()->GetType() == EnemyType::Boss)
					{
						Event e{ BOSS_DIED };
						event.args[0].go->GetComponent<Player>()->Notify(e, event.args[0].go);
					}
					else
					{
						Event e{ ENEMY_DIED };
						event.args[0].go->GetComponent<Player>()->Notify(e, event.args[0].go);
					}
				}
			}

			gameObject->GetComponent<Transform>()->SetLocalPosition({ -100, 0 });
			event.args[1].go->RemoveAllChilderen();
			event.args[1].go->GetComponent<Enemy>()->EnemyDied();
			event.args[1].go->RemoveComponent<Enemy>();
			event.args[1].go->RemoveComponent<State>();
			event.args[1].go->RemoveComponent<BezierPath>();
			event.args[1].go->AddComponent<ExplosionAnimation>();
		}
		if (event.id == PLAYER_HIT)
		{
			gameObject->GetComponent<Player>()->Notify(event, gameObject);
		}
	}
}