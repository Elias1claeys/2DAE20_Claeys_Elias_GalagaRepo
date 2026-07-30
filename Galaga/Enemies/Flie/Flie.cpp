#include "Flie.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Enemies/Enemie.h"

namespace dae
{
	Flie::Flie(GameObject* owner)
		: Component(owner)
	{
		GetOwner()->AddComponent<Enemie>(54.f);
	}

	void Flie::Update()
	{}
}