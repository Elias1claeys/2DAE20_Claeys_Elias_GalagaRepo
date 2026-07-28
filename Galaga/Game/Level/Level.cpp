#include "Level.h"
#include "Enemies/Bee/Bee.h"
#include "Game/Game.h"

namespace dae
{
	void Level::OnEnter()
	{
		m_pGame->GetOwner()->AddComponent<Bee>();
	}

	void Level::Update(float)
	{

	}

	void Level::OnExit()
	{

	}

	std::unique_ptr<GameState> Level::GoToNextState()
	{
		return nullptr;
	}
}