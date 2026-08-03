#include "InFormation.h"
#include "StateMachine/State.h"
#include "Enemies/Enemy.h"
#include "GameEvents.h"

namespace dae
{
	InFormation::InFormation(State* state)
		: GameState(state)
	{
		m_pState->GetOwner()->GetComponent<Enemy>()->Notify(Event{ ENEMY_IN_FORMATION });
	}

	void InFormation::OnEnter()
	{
		m_pState->GetOwner()->GetComponent<Enemy>()->SetEnemieTexture(1.5f);
	}
}