#include "CollisionObserver.h"
#include "Components/Transform.h"
#include "Event/Event.h"
#include "GameEvents.h"
#include "Enemies/EnemySpawner/EnemySpawner.h"
#include "Collider/Collider.h"

namespace dae
{
	void Collision::OnNotify(GameObject* bullet, const Event& event)
	{
		if (event.id == ENEMY_HIT)
		{
			bullet->GetParent()->GetComponent<EnemySpawner>()->EnemyBackInFormation();
			bullet->RemoveAllComponents();
			event.args[0].go->RemoveAllComponents();
		}
	}
}