#include "StateMachine/GameState.h"
#include "EnemyState.h"

namespace dae
{
	class FlyDive : public EnemyState
	{
	public:
		explicit FlyDive(State* state);
		virtual ~FlyDive() = default;
		FlyDive(const FlyDive& other) = delete;
		FlyDive(FlyDive&& other) = delete;
		FlyDive& operator=(const FlyDive& other) = delete;
		FlyDive& operator=(FlyDive&& other) = delete;

		void OnEnter() override;
		void Update(float) override;
		void OnExit() override {};

		std::unique_ptr<GameState> GoToNextState() override;
	};
}