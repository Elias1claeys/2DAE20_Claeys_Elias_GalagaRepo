#include "InFormation.h"
#include "StateMachine/State.h"
#include "Enemies/Enemy.h"
#include "GameEvents.h"
#include "Components/Transform.h"
#include "Bombing.h"
#include "BeamAttack.h"

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
		if (m_pState->GetOwner()->GetComponent<Enemy>()->GetType() == EnemyType::Boss && 
			m_pState->GetOwner()->GetComponent<Enemy>()->DoesBeamAttack())
		{
			return std::make_unique<BeamAttack>(m_pState);
		}
		else
		{
			return std::make_unique<Bombing>(m_pState);
		}
		
	}
}