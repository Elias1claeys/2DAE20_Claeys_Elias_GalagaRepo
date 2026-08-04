#include "Core/GameObject.h"
#include "Event/Observer.h"

namespace dae
{
	class Collision : public Observer
	{
	public:
		void OnNotify(GameObject* gameObject, const Event& event) override;
	};
}