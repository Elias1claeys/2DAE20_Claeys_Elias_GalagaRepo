#include "Core/GameObject.h"

namespace dae
{
	class Flie : public Component
	{

	public:
		Flie(GameObject* owner);
		virtual ~Flie() = default;
		Flie(const Flie& other) = delete;
		Flie(Flie&& other) = delete;
		Flie& operator=(const Flie& other) = delete;
		Flie& operator=(Flie&& other) = delete;

		void Update() override;

	private:
	};
}