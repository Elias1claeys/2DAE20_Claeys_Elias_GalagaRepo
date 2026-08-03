#include "Player.h"
#include "Components/Transform.h"
#include "Components/Texture.h"
#include "Core/DeltaTime.h"
#include "Input/InputManager.h"
#include "PlayerControls.h"

namespace dae
{
	Player::Player(GameObject* owner) : Component(owner)
	{
		GetOwner()->AddComponent<Texture>()->SetTexture("Galaga2.png");
		GetOwner()->GetComponent<Texture>()->SetSize({ 40, 40 });
		GetOwner()->GetComponent<Texture>()->SetSourceRect(109.5f, 1.5f, 15.f, 15.f);
		GetOwner()->GetComponent<Transform>()->SetLocalPosition({ 256.f, 462.f });

		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_LEFT, std::make_shared<Move>(this, glm::vec2{ -1.0f, 0.0f }));
		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_RIGHT, std::make_shared<Move>(this, glm::vec2{ 1.0f, 0.0f }));
		InputManager::GetInstance().BindKeyBoardCommand(SDL_SCANCODE_SPACE, std::make_shared<Attack>(this));
	}

	void Player::Update()
	{
		auto transform = GetOwner()->GetComponent<Transform>();
		glm::vec2 pos = transform->GetWorldPosition();

		pos += m_Direction * m_Speed * Time::GetInstance().GetDeltaTime();

		if (pos.x <= 0 || pos.x >= 472)
		{
			m_Direction = glm::vec2{ 0.0f, 0.0f };
		}
		else
		{
			transform->SetLocalPosition(pos);
		}
	}

	void Player::SetDirection(const glm::vec2& direction)
	{
		m_Direction = direction;
	}

	void Player::Shoot()
	{
		
	}
}