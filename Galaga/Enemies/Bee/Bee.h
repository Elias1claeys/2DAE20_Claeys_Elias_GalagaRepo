#include "Core/GameObject.h"

namespace dae
{
	class Bee : public Component
	{

	public:
		Bee(GameObject* owner);
		virtual ~Bee() = default;
		Bee(const Bee& other) = delete;
		Bee(Bee&& other) = delete;
		Bee& operator=(const Bee& other) = delete;
		Bee& operator=(Bee&& other) = delete;

		void Update() override;

	private:
	};
}