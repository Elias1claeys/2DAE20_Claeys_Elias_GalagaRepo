#include "FlyDive.h"
#include "Enemies/Path/BezierPath.h"

namespace dae
{
	FlyDive::FlyDive(State* state)
		:EnemyState(state)
	{
	}

	void FlyDive::OnEnter()
	{
		glm::vec2 endPoint = m_pState->GetOwner()->GetComponent<Enemy>()->GetPlayerPos();
		m_pState->GetOwner()->GetComponent<BezierPath>()->SetWeavePath(endPoint, 5, 15.f);

	}

	void FlyDive::Update(float)
	{

	}

	std::unique_ptr<GameState> FlyDive::GoToNextState()
	{
		return nullptr;
	}
}