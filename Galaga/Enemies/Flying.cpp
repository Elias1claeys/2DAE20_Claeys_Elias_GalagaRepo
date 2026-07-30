#include "Flying.h"
#include "StateMachine/State.h"
#include <glm/gtc/constants.hpp>

namespace dae
{
	Flying::Flying(State* state, BezierSegment bezierSegment, float loopPoint)
		: GameState(state), m_BezierSegment(bezierSegment), m_LoopPoint(loopPoint)
	{}

	Flying::Flying(State* state, BezierSegment bezierSegment)
		: GameState(state), m_BezierSegment(bezierSegment)
	{}

	void Flying::OnEnter()
	{
	}

	void Flying::Update(float deltaTime)
	{
		if (m_T >= 1.f)
		{
			//m_pState->GoToNextStage();
			return;
		}

		auto transform = m_pState->GetOwner()->GetComponent<dae::Transform>();

		switch (m_Phase)
		{
		case Phase::preLoop:
			BezierMovement(deltaTime, transform);

			if (m_T >= m_LoopPoint && m_LoopPoint != 0.f)
			{
				m_RotationCenter = glm::vec2(transform->GetWorldPosition().x, transform->GetWorldPosition().y - 50.f);
				glm::vec2 toCurrent = transform->GetWorldPosition() - m_RotationCenter;
				m_LoopStartAngle = std::atan2(toCurrent.y, toCurrent.x);
				m_LoopAngle = m_LoopStartAngle;

				m_Phase = Phase::loop;
			}
			break;

		case Phase::loop:
			
			Looping(deltaTime, transform);
			break;

		case Phase::postLoop:
			BezierMovement(deltaTime, transform);
			break;
		}

		
	}

	void Flying::OnExit()
	{
		m_pState->GetOwner()->GetComponent<dae::Transform>()->SetLocalPosition(m_BezierSegment.endPoint);
	}

	std::unique_ptr<GameState> Flying::GoToNextState()
	{
		return nullptr;
	}
}

void dae::Flying::BezierMovement(float deltaTime, Transform* transform)
{
	m_T += 0.7f * deltaTime;

	glm::vec2 newPos = ((1 - m_T) * (1 - m_T) * m_BezierSegment.startPoint) +
		2 * (1 - m_T) * m_T * m_BezierSegment.curvePoint +
		m_T * m_T * m_BezierSegment.endPoint;

	transform->SetLocalPosition(newPos);
}

void dae::Flying::Looping(float deltaTime, Transform* transform)
{
	m_LoopAngle -= 7.f * deltaTime;

	glm::vec2 newPos = m_RotationCenter +
		glm::vec2(std::cos(m_LoopAngle), std::sin(m_LoopAngle)) * 50.f;

	transform->SetLocalPosition(newPos);

	if (m_LoopAngle <= m_LoopStartAngle - glm::two_pi<float>())
	{
		m_Phase = Phase::postLoop;
	}
}