#include "Bee.h"
#include "Enemies/Enemie.h"
#include "Components/Texture.h"
#include "Components/Transform.h"

namespace dae
{
	Bee::Bee(GameObject* owner)
		: Component(owner)
	{
		GetOwner()->AddComponent<Enemie>(18.f);
	}

	void Bee::Update()
	{}
}