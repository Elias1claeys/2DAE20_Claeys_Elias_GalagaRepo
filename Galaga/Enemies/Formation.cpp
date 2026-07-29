#include "Formation.h"
#include "StateMachine/State.h"

namespace dae
{
	Formation::Formation(State* state, glm::vec2 startPoint, glm::vec2 endPoint, glm::vec2 curvePoint)
		: GameState(state), m_StartPoint(startPoint), m_EndPoint(endPoint), m_CurvePoint(curvePoint)
	{
	}

	void Formation::OnEnter()
	{
		glm::vec2 spawnPoint = m_StartPoint - glm::normalize(m_EndPoint - m_StartPoint) * 50.0f;
		m_pState->GetOwner()->GetComponent<dae::Transform>()->SetLocalPosition(spawnPoint);
	}

	void Formation::Update(float deltaTime)
	{
		m_T += 0.5f * deltaTime; 

		auto transform = m_pState->GetOwner()->GetComponent<dae::Transform>();

		if (m_T >= 1.f)
		{
			transform->SetLocalPosition(m_EndPoint);
		}
		else
		{
			glm::vec2 newPos = ((1 - m_T) * (1 - m_T) * m_StartPoint) + 
								2 * (1 - m_T) * m_T * m_CurvePoint + 
								m_T * m_T * m_EndPoint;

			transform->SetLocalPosition(newPos);
		}
	}

	void Formation::OnExit()
	{}

	std::unique_ptr<GameState> Formation::GoToNextState()
	{
		return nullptr;
	}
}