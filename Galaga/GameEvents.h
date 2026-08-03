#include "Event/Event.h"

namespace dae {
	constexpr EventId ENEMY_IN_FORMATION = make_sdbm_hash("EnemyInFormation");
	constexpr EventId ENEMY_OUT_FORMATION = make_sdbm_hash("EnemyOutFormation");
	constexpr EventId ENEMY_SPAWNED = make_sdbm_hash("EnemySpawned");
}