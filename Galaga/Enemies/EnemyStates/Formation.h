#include "StateMachine/GameState.h"

namespace dae
{
	class Formation : public GameState
	{
	public:
		explicit Formation(State* state);
		virtual ~Formation() = default;
		Formation(const Formation& other) = delete;
		Formation(Formation&& other) = delete;
		Formation& operator=(const Formation& other) = delete;
		Formation& operator=(Formation&& other) = delete;

		void OnEnter() override;
		void Update(float) override {};
		void OnExit() override {};

		std::unique_ptr<GameState> GoToNextState() override { return nullptr; };
	};
}