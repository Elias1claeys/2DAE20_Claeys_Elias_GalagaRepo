#include "SoundObserver.h"
#include "GameEvents.h"

namespace dae
{
	SoundObserver::SoundObserver()
	{
		m_pAudio = &dae::SoundLocator::GetAudio();

		m_pAudio->RegisterSound(static_cast<dae::SoundId>(ENEMY_DIED), "Data/Audio/EnemyDies.mp3");
		m_pAudio->RegisterSound(static_cast<dae::SoundId>(GAME_STARTED), "Data/Audio/Start.mp3");
		m_pAudio->RegisterSound(static_cast<dae::SoundId>(PLAYER_SHOOT), "Data/Audio/PlayerShoot.mp3");
		m_pAudio->RegisterSound(static_cast<dae::SoundId>(BOSS_DIED), "Data/Audio/BossDeath.mp3");
		m_pAudio->RegisterSound(static_cast<dae::SoundId>(PLAYER_HIT), "Data/Audio/PlayerDies.mp3");
		m_pAudio->RegisterSound(static_cast<dae::SoundId>(PLAYER_DIED), "Data/Audio/PlayerDies.mp3");
		m_pAudio->RegisterSound(static_cast<dae::SoundId>(PLAYER_IN_BEAM), "Data/Audio/CapturedShip.mp3");
		m_pAudio->RegisterSound(static_cast<dae::SoundId>(BEAM_SHOT), "Data/Audio/TractorBeam.mp3");
	}

	void SoundObserver::OnNotify(GameObject* , const Event& event)
	{
		m_pAudio->Play(static_cast<dae::SoundId>(event.id), 1.f);
	}
}
