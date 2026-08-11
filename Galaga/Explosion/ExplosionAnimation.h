#include "Core/GameObject.h"

namespace dae
{
	class ExplosionAnimation : public Component
	{
	public:
		ExplosionAnimation(GameObject* owner);
		virtual ~ExplosionAnimation() = default;
		ExplosionAnimation(const ExplosionAnimation& other) = delete;
		ExplosionAnimation(ExplosionAnimation&& other) = delete;
		ExplosionAnimation& operator=(const ExplosionAnimation& other) = delete;
		ExplosionAnimation& operator=(ExplosionAnimation&& other) = delete;

		void Update() override;

	private:
		float m_Time = 0.2f;
		int m_Index = 0;
	};
}