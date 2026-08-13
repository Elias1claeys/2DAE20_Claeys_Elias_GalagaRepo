#pragma once
#include "Event/Subject.h"
#include "Core/GameObject.h"
#include "GameState.h"

namespace dae
{
	class State : public Component, public Subject 
	{
	public:

		State(GameObject* owner, std::unique_ptr<GameState> gameState);
		virtual ~State() = default;
		State(const State& other) = delete;
		State(State&& other) = delete;
		State& operator=(const State& other) = delete;
		State& operator=(State&& other) = delete;

		GameObject* GetOwner() const { return Component::GetOwner(); }

		void Update() override;
		void GoToNextStage();
		GameState* GetGameState() const { return m_pGameState.get(); }

	private:
		std::unique_ptr<GameState> m_pGameState;
		std::vector<std::unique_ptr<GameObject>> m_pGameObjects;
	};
}