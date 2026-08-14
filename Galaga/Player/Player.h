#pragma once

#include "Core/GameObject.h"
#include "Event/Subject.h"

namespace dae
{
	class EnemiesController;

	class Player : public Component, public Subject
	{
	public:
		Player(GameObject* owner, EnemiesController* enemiesController);
		virtual ~Player() = default;
		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

		void Update() override;
		void SetDirection(const glm::vec2& direction);
		void Shoot();
		void StuckInBeam(glm::vec2 flyPoint);

	private:
		bool m_CanShoot = true;
		bool m_StuckInBeam = false;
		float m_Speed = 100.0f;
		float m_Time = 0.f;
		glm::vec2 m_Direction{ 0.0f, 0.0f };
		glm::vec2 m_FlyPoint{ 0.f, 0.f };
		std::vector<std::unique_ptr<GameObject>> m_Bullets{};
		EnemiesController* m_EnemiesController{};
	};
}