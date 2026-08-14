#pragma once
#include "StateMachine/GameState.h"
#include "StateMachine/State.h"
#include "GameEvents.h"
#include "Enemies/Enemy.h"
#include "Enemies/EnemyTypes.h"

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

        virtual void EnemyHit()
        {
            m_pState->GetOwner()->GetComponent<Enemy>()->Notify(Event{ ENEMY_HIT_BEFORE_FORMATION });

            auto type = m_pState->GetOwner()->GetComponent<Enemy>()->GetType();
            Event e{ POINTS_GAINED };

            switch (type)
            {
            case EnemyType::Bee:
                e.args[0].i = 100;
                break;
            case EnemyType::Flie:
                e.args[0].i = 160;
                break;
            case EnemyType::Boss:
                e.args[0].i = 400;
                break;
            }

            m_pState->GetOwner()->GetComponent<Enemy>()->Notify(e);
        };
	};
}