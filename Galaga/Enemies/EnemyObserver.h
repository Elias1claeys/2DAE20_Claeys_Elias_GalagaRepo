#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
	class EnemyObserver : public Observer
	{
	public:
		void OnNotify(GameObject* entity, const Event& event) override;

		int GetEnemiesInFormation() const { return m_EnemiesInFormation; }

	private:
		int m_EnemiesInFormation = 0;
	};
}