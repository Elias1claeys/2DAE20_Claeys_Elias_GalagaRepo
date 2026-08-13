#include "StateMachine/GameState.h"
#include "EnemyState.h"

namespace dae
{
	class Bombing : public EnemyState
	{
	public:
		explicit Bombing(State* state);
		virtual ~Bombing() = default;
		Bombing(const Bombing& other) = delete;
		Bombing(Bombing&& other) = delete;
		Bombing& operator=(const Bombing& other) = delete;
		Bombing& operator=(Bombing&& other) = delete;

		void OnEnter() override;
		void Update(float) override {};
		void OnExit() override {};

		std::unique_ptr<GameState> GoToNextState() override;
	};
}