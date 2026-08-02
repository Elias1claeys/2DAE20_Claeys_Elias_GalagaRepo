#include "Bee.h"
#include "Enemies/Enemy.h"
#include "Components/Texture.h"
#include "Components/Transform.h"

namespace dae
{
	Bee::Bee(GameObject* owner)
		: Component(owner)
	{
		GetOwner()->AddComponent<Enemy>(18.f);
	}

	void Bee::Update()
	{}
}