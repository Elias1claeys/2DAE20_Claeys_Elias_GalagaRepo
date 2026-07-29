#include "StateMachine/GameState.h"
#include "Core/GameObject.h"

namespace dae
{
	class Start : public GameState
	{
	private:

		std::vector<std::unique_ptr<GameObject>> m_pGameModes;
		std::vector<std::unique_ptr<GameObject>> m_pHighScores;
		int m_SelectedButton{ 0 };

		void InitGameModes();
		void InitHighScores();

	public:
		
		explicit Start(State* state) : GameState(state) {}
		virtual ~Start() = default;
		Start(const Start& other) = delete;
		Start(Start&& other) = delete;
		Start& operator=(const Start& other) = delete;
		Start& operator=(Start&& other) = delete;
		
		void SelectButton(int direction);
		void GameModeSelected();

		void OnEnter() override;
		void Update(float ) override{}
		void OnExit() override;

		std::unique_ptr<GameState> GoToNextState() override;
	};
}