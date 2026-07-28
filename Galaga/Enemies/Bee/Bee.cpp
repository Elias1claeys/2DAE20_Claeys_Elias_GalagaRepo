#include "Bee.h"
#include "Components/Texture.h"
#include "Components/Transform.h"

namespace dae
{
	Bee::Bee(GameObject* owner)
		: Component(owner)
	{
		GetOwner()->AddComponent<Texture>();
		GetOwner()->GetComponent<Transform>()->SetLocalPosition(100, 100, 0);
		GetOwner()->GetComponent<Texture>()->SetTexture("Galaga2.png");

		float y = 19.5;
		float x = 1.5; //always + 18
		float size = 15;

		GetOwner()->GetComponent<Texture>()->SetSize({ 40, 40 });
		GetOwner()->GetComponent<Texture>()->SetSourceRect(x, y, size, size);
	}

	void Bee::Update()
	{}
}