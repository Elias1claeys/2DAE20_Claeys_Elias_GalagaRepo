#include "Enemie.h"
#include "Components/Texture.h"

namespace dae
{
	Enemie::Enemie(GameObject* owner, float yPosEnmie)
		: Component(owner)
	{
		GetOwner()->AddComponent<Texture>();
		GetOwner()->GetComponent<Texture>()->SetTexture("Galaga2.png");

		float y = 1.5f + yPosEnmie;
		float x = 1.5f;
		float size = 15.f;

		GetOwner()->GetComponent<Texture>()->SetSize({ 40, 40 });
		GetOwner()->GetComponent<Texture>()->SetSourceRect(x, y, size, size);
	}

	void Enemie::Update()
	{}
}