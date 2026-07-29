#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class State;
	class GameObject;

	class GameState
	{
	public:
		explicit GameState(State* state) : m_pState(state) {}
		virtual ~GameState() = default;
		GameState(const GameState& other) = delete;
		GameState(GameState&& other) = delete;
		GameState& operator=(const GameState& other) = delete;
		GameState& operator=(GameState&& other) = delete;
		
		void SetState(State* state) { m_pState = state; }

		virtual void OnEnter() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void OnExit() = 0;

		virtual std::unique_ptr<GameState> GoToNextState() = 0;

	protected:
		State* m_pState;
	};
}