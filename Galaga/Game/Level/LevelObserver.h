#include "Event/Observer.h"

namespace dae
{
	class Level;

	class LevelObserver final : public Observer
	{

	public:
		LevelObserver(Level* level);
		virtual ~LevelObserver() = default;
		LevelObserver(const LevelObserver& other) = delete;
		LevelObserver(LevelObserver&& other) = delete;
		LevelObserver& operator=(const LevelObserver& other) = delete;
		LevelObserver& operator=(LevelObserver&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;

	private:
		Level* m_Level;
		int m_DeadEnemies;
		int m_LevelIndex;
	};
}