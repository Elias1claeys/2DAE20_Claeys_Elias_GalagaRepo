#pragma once

#include "StateMachine/GameState.h"
#include "EnemyState.h"

namespace dae
{
	class InFormation : public EnemyState
	{
	public:
		explicit InFormation(State* state);
		virtual ~InFormation() = default;
		InFormation(const InFormation& other) = delete;
		InFormation(InFormation&& other) = delete;
		InFormation& operator=(const InFormation& other) = delete;
		InFormation& operator=(InFormation&& other) = delete;

		void OnEnter() override;
		void Update(float) override;
		void OnExit() override {};

		void EnemyHit() override {};

		std::unique_ptr<GameState> GoToNextState() override;
	};
}