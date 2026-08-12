#include "Player.h"
#include "Components/Transform.h"
#include "Components/Texture.h"
#include "Core/DeltaTime.h"
#include "Input/InputManager.h"
#include "PlayerControls.h"
#include "Bullet/Bullet.h"
#include "Enemies/EnemiesController/EnemiesController.h"
#include "Collider/Collider.h"
#include "GameEvents.h"

namespace dae
{
	Player::Player(GameObject* owner) : Component(owner)
	{
		GetOwner()->AddComponent<Texture>()->SetTexture("Galaga2.png");
		GetOwner()->GetComponent<Texture>()->SetSize({ 30, 30 });
		GetOwner()->GetComponent<Texture>()->SetSourceRect(109.5f, 1.5f, 15.f, 15.f);
		GetOwner()->GetComponent<Transform>()->SetLocalPosition({ 241.f, 442.f });

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

		m_Time += Time::GetInstance().GetDeltaTime();
		if (m_Time > 0.5f)
		{
			m_Time = 0.f;
			m_CanShoot = true;
		}
	}

	void Player::SetDirection(const glm::vec2& direction)
	{
		m_Direction = direction;
	}

	void Player::Shoot()
	{
		if (m_CanShoot)
		{
			auto bullet = std::make_unique<GameObject>();
			bullet->AddComponent<Bullet>(glm::vec2{ 0.0f, -1.0f });

			glm::vec2 playerPos = GetOwner()->GetComponent<Transform>()->GetWorldPosition();
			bullet->GetComponent<Transform>()->SetLocalPosition(playerPos + glm::vec2{ 0.f, -40.f });

			bullet->AddComponent<Collider>(glm::vec2{ 17.f, 7.f }, glm::vec2{ 5.f, 25.f });

			Event hitEvent{ ENEMY_HIT };
			GetOwner()->GetParent()->GetComponent<EnemiesController>()->AddEnemyCollisions(bullet.get(), hitEvent);

			bullet->SetParent(GetOwner()->GetParent(), false);
			m_Bullets.push_back(std::move(bullet));

			m_CanShoot = false;
		}
	}
}