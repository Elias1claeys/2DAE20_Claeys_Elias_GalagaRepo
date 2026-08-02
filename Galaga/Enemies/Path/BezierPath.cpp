#include "BezierPath.h"
#include "StateMachine/State.h"
#include <glm/gtc/constants.hpp>
#include "Enemies/Enemy.h"
#include "Core/DeltaTime.h"
#include "Enemies/EnemyObserver.h"
#include "GameEvents.h"
#include "StateMachine/GameState.h"

namespace dae
{
	BezierPath::BezierPath(GameObject* owner)
		: Component(owner)
	{}

	void BezierPath::Update()
	{
		if (m_T >= 1.f)
			return;

		auto transform = GetOwner()->GetComponent<dae::Transform>();
		glm::vec2 previousPos = transform->GetWorldPosition();

		switch (m_Phase)
		{
		case Phase::preLoop:
			BezierMovement(transform);

			if (m_T >= m_BezierSegment.loopPoint && m_BezierSegment.loopPoint != 0.f)
			{
				m_RotationCenter = glm::vec2(transform->GetWorldPosition().x, transform->GetWorldPosition().y - 50.f);
				glm::vec2 toCurrent = transform->GetWorldPosition() - m_RotationCenter;
				m_LoopStartAngle = std::atan2(toCurrent.y, toCurrent.x);
				m_LoopAngle = m_LoopStartAngle;

				m_Phase = Phase::loop;
			}
			break;

		case Phase::loop:
			
			Looping(transform);
			break;

		case Phase::postLoop:
			BezierMovement(transform);
			break;
		}

		if (m_T < 1.f)
		{
			GetOwner()->GetComponent<dae::Enemy>()->SetEnemieTexture(previousPos);
		}
		else
		{
			GetOwner()->GetComponent<dae::Transform>()->SetLocalPosition(m_BezierSegment.endPoint);
			GetOwner()->GetComponent<dae::State>()->GoToNextStage();
		}
	}

	void BezierPath::BezierMovement(Transform* transform)
	{
		float deltaTime = Time::GetInstance().GetDeltaTime();

		glm::vec2 derivative =
			2.0f * (1 - m_T) * (m_BezierSegment.curvePoint - m_BezierSegment.startPoint) +
			2.0f * m_T * (m_BezierSegment.endPoint - m_BezierSegment.curvePoint);

		float curveSpeed = glm::length(derivative);

		float movementSpeed = 300.0f; 

		m_T += (movementSpeed / curveSpeed) * deltaTime;

		glm::vec2 newPos = ((1 - m_T) * (1 - m_T) * m_BezierSegment.startPoint) +
			2 * (1 - m_T) * m_T * m_BezierSegment.curvePoint +
			m_T * m_T * m_BezierSegment.endPoint;

		transform->SetLocalPosition(newPos);
	}

	void BezierPath::Looping(Transform* transform)
	{
		m_LoopAngle -= 3.f * Time::GetInstance().GetDeltaTime();

		glm::vec2 newPos = m_RotationCenter +
			glm::vec2(std::cos(m_LoopAngle), std::sin(m_LoopAngle)) * 50.f;

		transform->SetLocalPosition(newPos);

		if (m_LoopAngle <= m_LoopStartAngle - glm::two_pi<float>())
		{
			m_Phase = Phase::postLoop;
		}
	}

	void BezierPath::SetNewPath(glm::vec2 curvePoint, glm::vec2 endPoint, float loopPoint)
	{
		m_BezierSegment.startPoint = GetOwner()->GetComponent<dae::Transform>()->GetWorldPosition();
		m_BezierSegment.curvePoint = curvePoint;
		m_BezierSegment.endPoint = endPoint;
		m_BezierSegment.loopPoint = loopPoint;
		m_T = 0.f;
	}

}

