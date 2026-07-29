#include "State.h"
#include "Core/DeltaTime.h"

namespace dae
{
	State::State(GameObject* owner, std::unique_ptr<GameState> gameState)
		: Component(owner)
	{
		m_pGameState = std::move(gameState);
		m_pGameState->SetState(this);
		m_pGameState->OnEnter();
	}

	void State::Update()
	{
		m_pGameState->Update(Time::GetInstance().GetDeltaTime());
	}

	void State::GoToNextStage()
	{
		auto nextstage = m_pGameState->GoToNextState();

		if (nextstage != nullptr)
		{
			m_pGameState->OnExit();
			m_pGameState = std::move(nextstage);
			m_pGameState->OnEnter();
		}
	}
}