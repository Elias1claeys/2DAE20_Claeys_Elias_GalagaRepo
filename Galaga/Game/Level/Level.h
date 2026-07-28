#include "Game/GameState.h"
#include <string>


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

	private:

		std::vector<glm::vec2> ReadPositionsFromFile(const std::string& filePath);

		std::vector<glm::vec2> m_SpawnPosBees;
		std::vector<glm::vec2> m_SpawnPosFlies;
		std::vector<glm::vec2> m_SpawnPosBosses;

		std::vector<std::unique_ptr<GameObject>> m_pBees;
		std::vector<std::unique_ptr<GameObject>> m_pFlies;
		std::vector<std::unique_ptr<GameObject>> m_pBosses;
	};
}