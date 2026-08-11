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
		if (m_BezierSegment.empty())
			return;

		auto transform = GetOwner()->GetComponent<dae::Transform>();
		glm::vec2 previousPos = transform->GetWorldPosition();

		switch (m_Phase)
		{
		case Phase::preLoop:
			BezierMovement(transform);

			if (m_T >= m_BezierSegment[m_PathIndex].loopPoint && m_BezierSegment[m_PathIndex].loopPoint != 0.f)
			{
				m_RotationCenter = glm::vec2(transform->GetWorldPosition().x, transform->GetWorldPosition().y - 50.f);
				glm::vec2 toCurrent = transform->GetWorldPosition() - m_RotationCenter;
				m_LoopStartAngle = std::atan2(toCurrent.y, toCurrent.x);
				m_LoopAngle = m_LoopStartAngle;

				if (previousPos.x <= m_RotationCenter.x)
					m_loopDirection = -1;
				else
					m_loopDirection = 1;

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
			if (m_PathIndex < m_BezierSegment.size() - 1)
			{
				m_PathIndex++;
				m_T = 0.f;
				m_Phase = Phase::preLoop;
				m_BezierSegment[m_PathIndex].startPoint = transform->GetWorldPosition();
			}
			else
			{
				GetOwner()->GetComponent<dae::Transform>()->SetLocalPosition(m_BezierSegment[m_PathIndex].endPoint);
				GetOwner()->GetComponent<dae::State>()->GoToNextStage();
				m_BezierSegment.clear();
			}
		}
	}

	void BezierPath::BezierMovement(Transform* transform)
	{
		float deltaTime = Time::GetInstance().GetDeltaTime();

		glm::vec2 derivative =
			2.0f * (1 - m_T) * (m_BezierSegment[m_PathIndex].curvePoint - m_BezierSegment[m_PathIndex].startPoint) +
			2.0f * m_T * (m_BezierSegment[m_PathIndex].endPoint - m_BezierSegment[m_PathIndex].curvePoint);

		float curveSpeed = glm::length(derivative);

		float movementSpeed = 250.0f; 

		m_T += (movementSpeed / curveSpeed) * deltaTime;

		glm::vec2 newPos = ((1 - m_T) * (1 - m_T) * m_BezierSegment[m_PathIndex].startPoint) +
			2 * (1 - m_T) * m_T * m_BezierSegment[m_PathIndex].curvePoint +
			m_T * m_T * m_BezierSegment[m_PathIndex].endPoint;

		transform->SetLocalPosition(newPos);
	}

	void BezierPath::Looping(Transform* transform)
	{
		m_LoopAngle += m_loopDirection * 4.f * Time::GetInstance().GetDeltaTime();

		glm::vec2 newPos = m_RotationCenter +
			glm::vec2(std::cos(m_LoopAngle), std::sin(m_LoopAngle)) * 50.f;

		transform->SetLocalPosition(newPos);

		float delta = m_loopDirection > 0
			? m_LoopAngle - m_LoopStartAngle
			: m_LoopStartAngle - m_LoopAngle;

		if (delta >= glm::two_pi<float>())
		{
			m_Phase = Phase::postLoop;
		}
	}

	void BezierPath::SetNewPath(glm::vec2 curvePoint, glm::vec2 endPoint, float loopPoint)
	{
		BezierSegment segment;
		segment.startPoint = GetOwner()->GetComponent<dae::Transform>()->GetWorldPosition();
		segment.curvePoint = curvePoint;
		segment.endPoint = endPoint;
		segment.loopPoint = loopPoint;

		m_BezierSegment.push_back(segment);
		m_T = 0.f;
	}
}

