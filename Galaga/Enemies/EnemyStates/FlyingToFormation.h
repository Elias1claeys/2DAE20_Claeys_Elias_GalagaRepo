#pragma once

#include "StateMachine/GameState.h"
#include "EnemyState.h"

namespace dae
{
	class FlyingToFormation : public EnemyState
	{
	public:
		explicit FlyingToFormation(State* state);
		virtual ~FlyingToFormation() = default;
		FlyingToFormation(const FlyingToFormation& other) = delete;
		FlyingToFormation(FlyingToFormation&& other) = delete;
		FlyingToFormation& operator=(const FlyingToFormation& other) = delete;
		FlyingToFormation& operator=(FlyingToFormation&& other) = delete;

		void OnEnter() override;
		void Update(float) override;
		void OnExit() override {};

		void EnemyHit() override;

		std::unique_ptr<GameState> GoToNextState() override;


	};
}