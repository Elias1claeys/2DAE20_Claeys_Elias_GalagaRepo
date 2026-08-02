#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
	class EnemyObserver : public Observer
	{
		GameObject* m_pEnemy{ nullptr };

	public:
		EnemyObserver(GameObject* enemy);
		virtual ~EnemyObserver() = default;
		EnemyObserver(const EnemyObserver& other) = delete;
		EnemyObserver(EnemyObserver&& other) = delete;
		EnemyObserver& operator=(const EnemyObserver& other) = delete;
		EnemyObserver& operator=(EnemyObserver&& other) = delete;

		void OnNotify(GameObject* entity, const Event& event) override;
	};
}