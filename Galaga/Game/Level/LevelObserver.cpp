#include "LevelObserver.h"
#include "GameEvents.h"
#include "Level.h"

namespace dae
{
	LevelObserver::LevelObserver(Level* level)
		: m_Level(level)
	{
	}

	void LevelObserver::OnNotify(GameObject* , const Event& event)
	{
		if (event.id == ENEMY_DIED)
			m_DeadEnemies++;

		if (m_DeadEnemies == 40)
		{
			m_DeadEnemies = 0;
			m_LevelIndex++;

			if (m_LevelIndex > 3)
				m_LevelIndex = 1;

			m_Level->LoadLevel(m_LevelIndex);
		}
	}
}