#include "FlyingToFormation.h"
#include "Enemies/Path/BezierPath.h"
#include "Enemies/Enemy.h"
#include "Enemies/EnemyStates/InFormation.h"
#include "StateMachine/State.h"
#include "GameEvents.h"

namespace dae
{
	FlyingToFormation::FlyingToFormation(State* state, glm::vec2 curvePoint, float loopPoint)
		: EnemyState(state), m_CurvePoint(curvePoint), m_LoopPoint(loopPoint)
	{}

	void FlyingToFormation::OnEnter()
	{
		glm::vec2 start = { 256.f, 256.f };
		glm::vec2 end = m_pState->GetOwner()->GetComponent<dae::Enemy>()->GetFormationPos();;

		glm::vec2 midpoint = (start + end) * 0.5f;

		glm::vec2 direction = glm::normalize(end - start);
		glm::vec2 perpendicular = { -direction.y, direction.x };

		float curveAmount = 50.f;

		glm::vec2 curvePoint = midpoint + perpendicular * curveAmount;

		m_pState->GetOwner()->GetComponent<BezierPath>()->SetNewPath(m_CurvePoint, start, m_LoopPoint);
		m_pState->GetOwner()->GetComponent<BezierPath>()->SetNewPath(curvePoint, end, 0);
	}

	std::unique_ptr<GameState> FlyingToFormation::GoToNextState()
	{
		return std::make_unique<InFormation>(m_pState);
	}

	void FlyingToFormation::EnemyHit()
	{
		m_pState->GetOwner()->GetComponent<Enemy>()->Notify(Event{ ENEMY_HIT_BEFORE_FORMATION });
	}
}