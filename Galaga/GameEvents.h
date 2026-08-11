#include "Event/Event.h"

namespace dae {
	constexpr EventId ENEMY_IN_FORMATION = make_sdbm_hash("EnemyInFormation");
	constexpr EventId ENEMY_HIT_BEFORE_FORMATION = make_sdbm_hash("EnemyHitBeforeFormation");
	constexpr EventId ENEMY_OUT_FORMATION = make_sdbm_hash("EnemyOutFormation");
	constexpr EventId ENEMY_SPAWNED = make_sdbm_hash("EnemySpawned");
	constexpr EventId ENEMY_HIT = make_sdbm_hash("EnemyHit");
	constexpr EventId GAME_STARTED = make_sdbm_hash("GameStarted");
}