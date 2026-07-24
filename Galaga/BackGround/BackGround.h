#include "Core/GameObject.h"

namespace dae
{
	class BackGround : public Component
	{
	public:

		BackGround(GameObject* pOwner);
		virtual ~BackGround() = default;
		BackGround(const BackGround& other) = delete;
		BackGround(BackGround&& other) = delete;
		BackGround& operator=(const BackGround& other) = delete;
		BackGround& operator=(BackGround&& other) = delete;

		void Update() override;

	private:
		std::unique_ptr<GameObject> m_Background1;
		std::unique_ptr<GameObject> m_Background2;

		float m_speed{ 250.f };
	};
}