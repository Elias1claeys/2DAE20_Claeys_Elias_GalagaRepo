#pragma once
#include "StateMachine/GameState.h"

namespace dae
{
    class EnemyState : public GameState
    {
    public:
        explicit EnemyState(State* state)
            : GameState(state)
        {}

        virtual ~EnemyState() = default;

        EnemyState(const EnemyState& other) = delete;
        EnemyState(EnemyState&& other) = delete;
        EnemyState& operator=(const EnemyState& other) = delete;
        EnemyState& operator=(EnemyState&& other) = delete;

        virtual void EnemyHit() = 0;
	};
}