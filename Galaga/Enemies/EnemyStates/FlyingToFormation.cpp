#include "FlyingToFormation.h"
#include "Enemies/Path/BezierPath.h"
#include "Enemies/Enemy.h"
#include "Enemies/EnemyStates/InFormation.h"
#include "StateMachine/State.h"

namespace dae
{
	FlyingToFormation::FlyingToFormation(State* state, glm::vec2 curvePoint, float loopPoint)
		: GameState(state), m_CurvePoint(curvePoint), m_LoopPoint(loopPoint)
	{}

	void FlyingToFormation::OnEnter()
	{
		glm::vec2 formationPos = m_pState->GetOwner()->GetComponent<dae::Enemy>()->GetFormationPos();
		m_pState->GetOwner()->GetComponent<BezierPath>()->SetNewPath(m_CurvePoint, formationPos, m_LoopPoint);
	}

	std::unique_ptr<GameState> FlyingToFormation::GoToNextState()
	{
		return std::make_unique<InFormation>(m_pState);
	}
}