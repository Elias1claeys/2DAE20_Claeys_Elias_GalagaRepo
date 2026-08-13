#include "BeamAttack.h"
#include "InFormation.h"

namespace dae
{
	BeamAttack::BeamAttack(State* state)
		: EnemyState(state)
	{
	}

	void BeamAttack::Update(float deltaTime)
	{
		if (!m_EndReached)
		{
			auto transform = m_pState->GetOwner()->GetComponent<Transform>();
			auto enemy = m_pState->GetOwner()->GetComponent<Enemy>();
			auto playerPos = enemy->GetPlayerPos();
			auto endPos = glm::vec2{ playerPos.x, playerPos.y - 100.f };
			auto currentPos = transform->GetWorldPosition();
			auto previousPos = transform->GetWorldPosition();

			glm::vec2 direction = endPos - currentPos;

			float distance = glm::length(direction);

			if (distance <= 2.f)
			{
				enemy->SetEnemieTexture(145.5f);
				m_EndReached = true;
				return;
			}

			direction = glm::normalize(direction);

			constexpr float speed = 200.f;

			currentPos += direction * speed * deltaTime;

			transform->SetLocalPosition(currentPos);
			enemy->SetEnemieTexture(previousPos);
		}
	}

	void BeamAttack::OnExit()
	{
		m_pState->GetOwner()->RemoveAllChilderen();
	}

	std::unique_ptr<GameState> BeamAttack::GoToNextState()
	{
		return nullptr;
	}
}