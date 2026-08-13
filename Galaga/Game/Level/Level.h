#include "StateMachine/GameState.h"
#include "Audio/SoundObserver.h"
#include "LevelObserver.h"
#include <string>


namespace dae
{
	class Level : public GameState
	{
	public:

		explicit Level(State* state) : GameState(state) {}
		virtual ~Level() = default;
		Level(const Level& other) = delete;
		Level(Level&& other) = delete;
		Level& operator=(const Level& other) = delete;
		Level& operator=(Level&& other) = delete;

		void OnEnter() override;
		void Update(float) override;
		void OnExit() override;

		std::unique_ptr<GameState> GoToNextState() override;

		void LoadLevel(int number);

	private:

		std::vector<glm::vec2> ReadPositionsFromFile(const std::string& filePath);
		void SpawnEnemies();
		
		std::vector<glm::vec2> m_FormationPosBees;
		std::vector<glm::vec2> m_FormationPosFlies;
		std::vector<glm::vec2> m_FormationPosBosses;

		std::vector<std::unique_ptr<GameObject>> m_GameObjects;
	};
}