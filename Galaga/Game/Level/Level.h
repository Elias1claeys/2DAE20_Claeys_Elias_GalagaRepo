#include "Game/GameState.h"

namespace dae
{
	class Level : public GameState
	{
	public:

		explicit Level(Game* game) : GameState(game) {}
		virtual ~Level() = default;
		Level(const Level& other) = delete;
		Level(Level&& other) = delete;
		Level& operator=(const Level& other) = delete;
		Level& operator=(Level&& other) = delete;

		void OnEnter() override;
		void Update(float) override;
		void OnExit() override;

		std::unique_ptr<GameState> GoToNextState() override;
	};
}