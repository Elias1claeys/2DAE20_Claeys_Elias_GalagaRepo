#include "SoundObserver.h"
#include "GameEvents.h"

namespace dae
{
	SoundObserver::SoundObserver()
	{
		m_pAudio = &dae::SoundLocator::GetAudio();

		m_pAudio->RegisterSound(static_cast<dae::SoundId>(ENEMY_HIT), "Data/Audio/EnemyDies.mp3");
		m_pAudio->RegisterSound(static_cast<dae::SoundId>(GAME_STARTED), "Data/Audio/Start.mp3");
	}

	void SoundObserver::OnNotify(GameObject* , const Event& event)
	{
		m_pAudio->Play(static_cast<dae::SoundId>(event.id), 1.f);
	}
}
