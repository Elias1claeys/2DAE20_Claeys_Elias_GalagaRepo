#include "Core/GameObject.h"

namespace dae
{
	class Enemie : public Component
	{

	public:
		Enemie(GameObject* owner, float yPosEnemie);
		virtual ~Enemie() = default;
		Enemie(const Enemie& other) = delete;
		Enemie(Enemie&& other) = delete;
		Enemie& operator=(const Enemie& other) = delete;
		Enemie& operator=(Enemie&& other) = delete;

		void Update() override;
		void SetEnemieTexture(glm::vec2 prevPos);
		void SetEnemieTexture(float x);

	private:
		float m_SourceRectY{};

	};
}