#include "Formation.h"
#include "StateMachine/State.h"
#include "Enemies/Enemy.h"

namespace dae
{
	Formation::Formation(State* state)
		: GameState(state)
	{
	}

	void Formation::OnEnter()
	{
		m_pState->GetOwner()->GetComponent<Enemy>()->SetEnemieTexture(1.5f);
	}
}