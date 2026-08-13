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

		int interval = rand() % 101 - 50;
		auto playerPos = m_pState->GetOwner()->GetComponent<Enemy>()->GetPlayerPos();
		glm::vec2 endPos = { playerPos.x - interval, playerPos.y };

		glm::vec2 curvePos = m_pState->GetOwner()->GetComponent<BezierPath>()->CalculateCurvePoint(startPos, endPos, 1.f);

		m_pState->GetOwner()->GetComponent<BezierPath>()->SetNewPath(curvePos, endPos, 1.f);
	}

	std::unique_ptr<GameState> Dive::GoToNextState()
	{
		glm::vec2 startPoint = m_pState->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		glm::vec2 endPoint = { 256, 600 };
		float curveAmount = 50.f;

		if (m_pState->GetOwner()->GetComponent<Enemy>()->GetType() == EnemyType::Bee)
		{
			auto playerPos = m_pState->GetOwner()->GetComponent<Enemy>()->GetPlayerPos();

			if (playerPos.x < startPoint.x)
			{
				endPoint = glm::vec2(0, 442.f);
				curveAmount = -75.f;
			}
			else
			{
				endPoint = glm::vec2(462.f, 442.f);
				curveAmount = 75.f;
			}
		}

		glm::vec2 curvePoint = m_pState->GetOwner()->GetComponent<BezierPath>()->CalculateCurvePoint(startPoint, endPoint, curveAmount);
		return std::make_unique<Flying>(m_pState, curvePoint, endPoint, 0.f);
	}
}