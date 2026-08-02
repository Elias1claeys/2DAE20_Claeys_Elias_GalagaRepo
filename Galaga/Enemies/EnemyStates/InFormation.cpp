#include "InFormation.h"
#include "StateMachine/State.h"
#include "Enemies/Enemy.h"

namespace dae
{
	InFormation::InFormation(State* state)
		: GameState(state)
	{
	}

	void InFormation::OnEnter()
	{
		m_pState->GetOwner()->GetComponent<Enemy>()->SetEnemieTexture(1.5f);
	}
}