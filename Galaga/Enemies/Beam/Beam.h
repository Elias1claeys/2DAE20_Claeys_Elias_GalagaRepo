#include "Core/GameObject.h"

namespace dae
{
	class Beam : public Component
	{
	public:
		Beam(GameObject* owner);
		virtual ~Beam() = default;
		Beam(const Beam& other) = delete;
		Beam(Beam&& other) = delete;
		Beam& operator=(const Beam& other) = delete;
		Beam& operator=(Beam&& other) = delete;

		void Update() override;
		bool CanPickPlayer();

	private:
		float m_Time = 0.5f;
		float m_Index = 0.f;
	};
}