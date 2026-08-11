#pragma once

#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
	class EnemiesController; // forward declaration

	class EnemyObserver : public Observer
	{
	public:

		EnemyObserver(EnemiesController* enemySpawner);
		virtual ~EnemyObserver() = default;
		EnemyObserver(const EnemyObserver& other) = delete;
		EnemyObserver(EnemyObserver&& other) = delete;
		EnemyObserver& operator=(const EnemyObserver& other) = delete;
		EnemyObserver& operator=(EnemyObserver&& other) = delete;

		void OnNotify(GameObject* entity, const Event& event) override;

	private:
		EnemiesController* m_EnemySpawner;
	};
}