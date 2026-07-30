#include "Boss.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Enemies/Enemie.h"

namespace dae
{
	Boss::Boss(GameObject* owner)
		: Component(owner)
	{
		GetOwner()->AddComponent<Enemie>(90.f);
	}

	void Boss::Update()
	{}
}