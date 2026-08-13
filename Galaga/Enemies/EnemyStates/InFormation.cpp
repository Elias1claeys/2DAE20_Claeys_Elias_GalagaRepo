#include "InFormation.h"
#include "StateMachine/State.h"
#include "Enemies/Enemy.h"
#include "GameEvents.h"
#include "Components/Transform.h"
#include "Bombing.h"

namespace dae
{
	InFormation::InFormation(State* state)
		: EnemyState(state)
	{
		m_pState->GetOwner()->GetComponent<Enemy>()->Notify(Event{ ENEMY_IN_FORMATION });
	}

	void InFormation::OnEnter()
	{
		m_pState->GetOwner()->GetComponent<Enemy>()->SetEnemieTexture(1.5f);
	}

	void InFormation::Update(float)
	{
		glm::vec2 formationPos = m_pState->GetOwner()->GetComponent<Enemy>()->GetFormationPos();
		m_pState->GetOwner()->GetComponent<Transform>()->SetLocalPosition(formationPos);
	}

	std::unique_ptr<GameState> InFormation::GoToNextState()
	{
		return std::make_unique<Bombing>(m_pState);
	}
}