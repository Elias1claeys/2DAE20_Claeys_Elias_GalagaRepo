#pragma once

#include "Core/GameObject.h"
#include "Event/Observer.h"
#include "Player/Player.h"

namespace dae
{
	class EnemiesController; // forward declaration

	class EnemyObserver : public Observer
	{
	public:

		EnemyObserver(EnemiesController* enemySpawner, Player* player);
		virtual ~EnemyObserver() = default;
		EnemyObserver(const EnemyObserver& other) = delete;
		EnemyObserver(EnemyObserver&& other) = delete;
		EnemyObserver& operator=(const EnemyObserver& other) = delete;
		EnemyObserver& operator=(EnemyObserver&& other) = delete;

		void OnNotify(GameObject* entity, const Event& event) override;

	private:
		EnemiesController* m_EnemySpawner;
		Player* m_Player;
	};
}