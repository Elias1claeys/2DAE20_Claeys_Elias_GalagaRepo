#include "FlyDive.h"
#include "Flying.h"
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
		glm::vec2 startPoint = m_pState->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		glm::vec2 endPoint = { 256, 600 };
		glm::vec2 curvePoint = m_pState->GetOwner()->GetComponent<BezierPath>()->CalculateCurvePoint(startPoint, endPoint, 50.f);

		return std::make_unique<Flying>(m_pState, curvePoint, endPoint);
	}
}