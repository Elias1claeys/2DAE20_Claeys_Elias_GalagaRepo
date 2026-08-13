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
		if (m_T > 1.f)
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

		if (m_T > 1.f)
		{
			if (m_IsWeaving && m_WeaveIndex + 1 < m_WeaveSegments.size())
			{
				++m_WeaveIndex;
				m_BezierSegment = m_WeaveSegments[m_WeaveIndex];
				m_T = 0.f;
			}
			else
			{
				m_IsWeaving = false;
				GetOwner()->GetComponent<dae::State>()->GoToNextStage();
			}
		}
		else
		{
			GetOwner()->GetComponent<dae::Enemy>()->SetEnemieTexture(previousPos);
		}
	}

	void BezierPath::BezierMovement(Transform* transform)
	{
		float deltaTime = Time::GetInstance().GetDeltaTime();

		glm::vec2 derivative =
			2.0f * (1 - m_T) * (m_BezierSegment.curvePoint - m_BezierSegment.startPoint) +
			2.0f * m_T * (m_BezierSegment.endPoint - m_BezierSegment.curvePoint);

		float curveSpeed = glm::length(derivative);

		float movementSpeed = 250.0f; 

		m_T += (movementSpeed / curveSpeed) * deltaTime;

		glm::vec2 newPos = ((1 - m_T) * (1 - m_T) * m_BezierSegment.startPoint) +
			2 * (1 - m_T) * m_T * m_BezierSegment.curvePoint +
			m_T * m_T * m_BezierSegment.endPoint;

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

		m_BezierSegment = segment;
		m_T = 0.f;
	}

	void BezierPath::SetWeavePath(glm::vec2 endPoint, int numSegments, float amplitude)
	{
		glm::vec2 start = GetOwner()->GetComponent<dae::Transform>()->GetWorldPosition();
		glm::vec2 fullDir = endPoint - start;

		m_WeaveSegments.clear();
		m_WeaveIndex = 0;
		m_IsWeaving = true;

		glm::vec2 segStart = start;
		float sign = 1.f;

		for (int i = 0; i < numSegments; ++i)
		{
			glm::vec2 segEnd = start + fullDir * (static_cast<float>(i + 1) / numSegments);
			glm::vec2 curvePoint = CalculateCurvePoint(segStart, segEnd, amplitude * sign);

			m_WeaveSegments.push_back({ segStart, segEnd, curvePoint, 0.f });

			segStart = segEnd;
			sign *= -1.f; // alternate left/right
		}

		m_BezierSegment = m_WeaveSegments[0];
		m_T = 0.f;
	}

	glm::vec2 BezierPath::CalculateCurvePoint(glm::vec2 start, glm::vec2 end, float curveAmount)
	{
		glm::vec2 midpoint = (start + end) * 0.5f;

		glm::vec2 direction = glm::normalize(end - start);
		glm::vec2 perpendicular = { -direction.y, direction.x };

		return midpoint + perpendicular * curveAmount;
	}
}

