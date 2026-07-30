#include "Core/GameObject.h"

namespace dae
{
	class Boss : public Component
	{

	public:
		Boss(GameObject* owner);
		virtual ~Boss() = default;
		Boss(const Boss& other) = delete;
		Boss(Boss&& other) = delete;
		Boss& operator=(const Boss& other) = delete;
		Boss& operator=(Boss&& other) = delete;

		void Update() override;

	private:
	};
}