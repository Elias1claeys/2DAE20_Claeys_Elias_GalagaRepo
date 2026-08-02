#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
	class EnemyObserver : public Observer
	{
		GameObject* m_pEnemy{ nullptr };

	public:
		void OnNotify(GameObject* entity, const Event& event) override;
	};
}