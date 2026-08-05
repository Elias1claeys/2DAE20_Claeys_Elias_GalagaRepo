#include "CollisionObserver.h"
#include "Components/Transform.h"
#include "Event/Event.h"
#include "GameEvents.h"
#include "Enemies/EnemySpawner/EnemySpawner.h"
#include "Collider/Collider.h"
#include "Enemies/EnemyStates/Dead.h"
#include "Enemies/Enemy.h"

namespace dae
{
	void Collision::OnNotify(GameObject* bullet, const Event& event)
	{
		if (event.id == ENEMY_HIT)
		{
			event.args[0].go->GetComponent<Enemy>()->Notify(event);
			bullet->RemoveAllComponents();
			event.args[0].go->RemoveAllComponents();
		}
	}
}