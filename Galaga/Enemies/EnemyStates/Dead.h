#include "StateMachine/GameState.h"

namespace dae
{
	class Dead : public GameState
	{
	public:
		explicit Dead(State* state);
		virtual ~Dead() = default;
		Dead(const Dead& other) = delete;
		Dead(Dead&& other) = delete;
		Dead& operator=(const Dead& other) = delete;
		Dead& operator=(Dead&& other) = delete;

		void OnEnter() override;
		void Update(float) override;
		void OnExit() override {};

		std::unique_ptr<GameState> GoToNextState() override { return nullptr; };
	};
}