#include "Dive.h"
#include "Enemies/Path/BezierPath.h"
#include "Flying.h"

namespace dae
{
	Dive::Dive(State* state)
		: EnemyState(state)
	{
	}

	void Dive::OnEnter()
	{
		glm::vec2 startPos = m_pState->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		glm::vec2 endPos = m_pState->GetOwner()->GetComponent<Enemy>()->GetPlayerPos();
		glm::vec2 curvePos = m_pState->GetOwner()->GetComponent<BezierPath>()->CalculateCurvePoint(startPos, endPos, 1.f);
		m_pState->GetOwner()->GetComponent<BezierPath>()->SetNewPath(curvePos, endPos, 1.f);
	}

	std::unique_ptr<GameState> Dive::GoToNextState()
	{
		if (m_pState->GetOwner()->GetComponent<Enemy>()->GetType() == EnemyType::Boss)
		{
			glm::vec2 startPoint = m_pState->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
			glm::vec2 endPoint = { 256, 600 };
			glm::vec2 curvePoint = m_pState->GetOwner()->GetComponent<BezierPath>()->CalculateCurvePoint(startPoint, endPoint, 50.f);

			return std::make_unique<Flying>(m_pState, curvePoint, endPoint);
		}
		else
		{
			return nullptr;
		}
	}
}