#include "StateMachine/GameState.h"
#include "EnemyState.h"

namespace dae
{
	class Dive : public EnemyState
	{
	public:
		explicit Dive(State* state);
		virtual ~Dive() = default;
		Dive(const Dive& other) = delete;
		Dive(Dive&& other) = delete;
		Dive& operator=(const Dive& other) = delete;
		Dive& operator=(Dive&& other) = delete;

		void OnEnter() override;
		void Update(float) override {};
		void OnExit() override {};

		std::unique_ptr<GameState> GoToNextState() override;
	};
}