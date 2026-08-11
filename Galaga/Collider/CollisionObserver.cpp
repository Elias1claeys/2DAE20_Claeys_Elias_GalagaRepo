#include "CollisionObserver.h"
#include "Components/Transform.h"
#include "Event/Event.h"
#include "GameEvents.h"
#include "Enemies/EnemySpawner/EnemySpawner.h"
#include "Collider/Collider.h"
#include "Enemies/EnemyStates/Dead.h"
#include "Enemies/Enemy.h"
#include "StateMachine/State.h"
#include "Enemies/EnemyStates/EnemyState.h"

namespace dae
{
	void Collision::OnNotify(GameObject* bullet, const Event& event)
	{
		if (event.id == ENEMY_HIT)
		{
			if (auto stateComp = event.args[0].go->GetComponent<State>())
			{
				if (auto enemyState = dynamic_cast<EnemyState*>(stateComp->GetGameState()))
				{
					enemyState->EnemyHit();
				}
			}

			bullet->RemoveAllComponents();
			event.args[0].go->RemoveAllComponents();
		}
	}
}