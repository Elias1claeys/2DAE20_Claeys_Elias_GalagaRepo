#include "StateMachine/GameState.h"

namespace dae
{
	class InFormation : public GameState
	{
	public:
		explicit InFormation(State* state);
		virtual ~InFormation() = default;
		InFormation(const InFormation& other) = delete;
		InFormation(InFormation&& other) = delete;
		InFormation& operator=(const InFormation& other) = delete;
		InFormation& operator=(InFormation&& other) = delete;

		void OnEnter() override;
		void Update(float) override {};
		void OnExit() override {};

		std::unique_ptr<GameState> GoToNextState() override { return nullptr; };
	};
}