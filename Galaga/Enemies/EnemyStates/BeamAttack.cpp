#include "BeamAttack.h"
#include "InFormation.h"
#include "Enemies/Beam/Beam.h"
#include "Flying.h"

namespace dae
{
	BeamAttack::BeamAttack(State* state)
		: EnemyState(state)
	{
		
	}

	void BeamAttack::Update(float deltaTime)
	{
		if (!m_EndReached)
		{
			auto transform = m_pState->GetOwner()->GetComponent<Transform>();
			auto enemy = m_pState->GetOwner()->GetComponent<Enemy>();
			auto playerPos = enemy->GetPlayerPos();
			auto endPos = glm::vec2{ playerPos.x, playerPos.y - 100.f };
			auto currentPos = transform->GetWorldPosition();
			auto previousPos = transform->GetWorldPosition();

			glm::vec2 direction = endPos - currentPos;

			float distance = glm::length(direction);

			if (distance <= 2.f)
			{
				enemy->SetEnemieTexture(145.5f);
				m_EndReached = true;

				m_Beam = std::make_unique<GameObject>();
				m_Beam->AddComponent<Beam>();
				m_Beam->SetParent(m_pState->GetOwner(), false);

				Event e{ BEAM_SHOT };
				m_pState->GetOwner()->GetComponent<Enemy>()->Notify(e);
				return;
			}

			direction = glm::normalize(direction);

			constexpr float speed = 200.f;

			currentPos += direction * speed * deltaTime;

			transform->SetLocalPosition(currentPos);
			enemy->SetEnemieTexture(previousPos);
		}
		else
		{
			if (!m_Beam->HasComponent<Beam>())
			{
				m_pState->GoToNextStage();
			}
			else if(m_Beam->GetComponent<Beam>()->CanPickPlayer() && !m_PlayerInBeam)
			{
				glm::vec2 playerPos = m_pState->GetOwner()->GetComponent<Enemy>()->GetPlayerPos();
				glm::vec2 enemyPos = m_pState->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
				glm::vec2 beamPos = { enemyPos.x - 5.f, enemyPos.y + 50.f };

				if (playerPos.x > beamPos.x && playerPos.x < beamPos.x + 40)
				{
					Event e{ PLAYER_IN_BEAM };
					e.args[0].v2 = beamPos;

					m_pState->GetOwner()->GetComponent<Enemy>()->Notify(e);
					m_PlayerInBeam = true;
				}
			}
		}
	}

	void BeamAttack::OnExit()
	{
		m_pState->GetOwner()->RemoveAllChilderen();
	}

	std::unique_ptr<GameState> BeamAttack::GoToNextState()
	{
		glm::vec2 startPoint = m_pState->GetOwner()->GetComponent<Transform>()->GetWorldPosition();
		glm::vec2 endPoint = { 256, 600 };
		glm::vec2 curvePoint = m_pState->GetOwner()->GetComponent<BezierPath>()->CalculateCurvePoint(startPoint, endPoint, 50.f);

		return std::make_unique<Flying>(m_pState, curvePoint, endPoint);
	}
}