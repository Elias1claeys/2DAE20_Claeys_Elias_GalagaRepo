#include "PlayerControls.h"
#include "Player.h"

namespace dae
{
	Move::Move(Player* actor, glm::vec2 dir)
		: m_Actor(actor), m_Direction(dir)
	{}

	void Move::Execute(KeyState state)
	{
		switch (state)
		{
		case dae::KeyState::Down:
			m_Actor->SetDirection(m_Direction);
			break;
		case dae::KeyState::Up:
			m_Actor->SetDirection(glm::vec2{ 0.0f, 0.0f });
			break;
		}
	}

	Attack::Attack(Player* actor)
		: m_Actor(actor)
	{}

	void Attack::Execute(KeyState state)
	{
		switch (state)
		{
		case dae::KeyState::Down:
			m_Actor->Shoot();
			break;
		}
	}
}