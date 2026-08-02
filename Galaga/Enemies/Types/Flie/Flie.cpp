#include "Flie.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Enemies/Enemy.h"

namespace dae
{
	Flie::Flie(GameObject* owner)
		: Component(owner)
	{
		GetOwner()->AddComponent<Enemy>(54.f);
	}

	void Flie::Update()
	{}
}