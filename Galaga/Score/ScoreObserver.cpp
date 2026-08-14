#include "ScoreObserver.h"
#include "GameEvents.h"
#include <string>

namespace dae
{
	ScoreObserver::ScoreObserver(Text* text)
		: m_Text(text)
	{
	}

	void ScoreObserver::OnNotify(GameObject*, const Event& event)
	{
		if (event.id == POINTS_GAINED)
		{
			m_Score += event.args[0].i;

			m_Text->SetText(std::to_string(m_Score));
		}
	}
}