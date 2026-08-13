#include "FlyingToFormation.h"
#include "Enemies/Path/BezierPath.h"
#include "Enemies/Enemy.h"
#include "Enemies/EnemyStates/InFormation.h"
#include "StateMachine/State.h"
#include "GameEvents.h"
#include "Core/DeltaTime.h"

namespace dae
{
	FlyingToFormation::FlyingToFormation(State* state)
		: EnemyState(state)
	{}

	void FlyingToFormation::OnEnter()
	{
		glm::vec2 currentPos = m_pState->GetOwner()->GetComponent<dae::Transform>()->GetWorldPosition();
		
		if (currentPos.y >= 512.f)
		{
			m_pState->GetOwner()->GetComponent<dae::Transform>()->SetLocalPosition({ 256, -50 });
		}
	}

	void FlyingToFormation::Update(float deltaTime)
	{
		auto transform = m_pState->GetOwner()->GetComponent<Transform>();
		auto enemy = m_pState->GetOwner()->GetComponent<Enemy>();
		auto formationPos = enemy->GetFormationPos();
		auto currentPos = transform->GetWorldPosition();
		auto previousPos = transform->GetWorldPosition();

		glm::vec2 direction = formationPos - currentPos;

		float distance = glm::length(direction);

		if (distance <= 2.f)
		{
			m_pState->GoToNextStage();
			return;
		}

		direction = glm::normalize(direction);

		constexpr float speed = 200.f;

		currentPos += direction * speed * deltaTime;

		transform->SetLocalPosition(currentPos);
		enemy->SetEnemieTexture(previousPos);
	}

	std::unique_ptr<GameState> FlyingToFormation::GoToNextState()
	{
		return std::make_unique<InFormation>(m_pState);
	}
}