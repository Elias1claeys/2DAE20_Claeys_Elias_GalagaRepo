#include "Flying.h"
#include "FlyingToFormation.h"

namespace dae
{
	Flying::Flying(State* state, glm::vec2 curvePoint, glm::vec2 endPoint, float loopPoint)
		: EnemyState(state), m_CurvePoint(curvePoint), m_LoopPoint(loopPoint), m_EndPoint(endPoint)
	{}

	void Flying::OnEnter()
	{
		m_pState->GetOwner()->GetComponent<BezierPath>()->SetNewPath(m_CurvePoint, m_EndPoint, m_LoopPoint);
	}

	std::unique_ptr<GameState> Flying::GoToNextState()
	{
		return std::make_unique<FlyingToFormation>(m_pState);
	}
}