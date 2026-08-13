#include "Bombing.h"
#include "StateMachine/State.h"
#include "Components/Transform.h"
#include "Enemies/Path/BezierPath.h"
#include "Enemies/Enemy.h"
#include "GameEvents.h"

namespace dae
{
	Bombing::Bombing(State* state)
		: EnemyState(state)
	{}

	void Bombing::OnEnter()
	{
		auto pos = m_pState->GetOwner()->GetComponent<Transform>()->GetWorldPosition();

		glm::vec2 curvePoint;

		if (pos.x < 256.f)
		{
			curvePoint = { 750.f, 200.f };
		}
		else
		{
			curvePoint = { -238.f, 200.f };
		}

		m_pState->GetOwner()->GetComponent<BezierPath>()->SetNewPath(curvePoint, { 256, 256 }, 0.f);
	}

	std::unique_ptr<GameState> Bombing::GoToNextState()
	{
		return nullptr;
	}
}