#include "Core/GameObject.h"
#include "Event/Observer.h"
#include "Audio/SoundSystem.h"

namespace dae
{
	class SoundObserver final : public Observer
	{
	private:
		SoundSystem* m_pAudio;
		int m_EmeraldsCollected{};

	public:
		SoundObserver();
		virtual ~SoundObserver() = default;
		SoundObserver(const SoundObserver& other) = delete;
		SoundObserver(SoundObserver&& other) = delete;
		SoundObserver& operator=(const SoundObserver& other) = delete;
		SoundObserver& operator=(SoundObserver&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}