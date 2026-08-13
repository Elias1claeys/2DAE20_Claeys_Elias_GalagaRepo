#pragma once
#include "Core/GameObject.h"
#include "Event/Subject.h"
#include "Enemies/EnemyTypes.h"
#include "Player/Player.h"
#include "Components/Transform.h"

namespace dae
{
	class Enemy : public Component, public Subject
	{

	public:
		
		Enemy(GameObject* owner, glm::vec2 formationPos, float yPosEnemie, EnemyType type, GameObject* player);
		virtual ~Enemy() = default;
		Enemy(const Enemy& other) = delete;
		Enemy(Enemy&& other) = delete;
		Enemy& operator=(const Enemy& other) = delete;
		Enemy& operator=(Enemy&& other) = delete;

		void Update() override;
		void Notify(Event event);
		void SetEnemieTexture(glm::vec2 prevPos);
		void SetEnemieTexture(float x);
		void AddToFormationPos(glm::vec2 dir);
		void SetBeamAttack(bool beamAttack) { m_BeamAttack = beamAttack; }
		void EnemyDied() { m_IsDead = true; }
		bool DoesBeamAttack() { return m_BeamAttack; }
		bool IsBossKilled();
		bool IsDead() { return m_IsDead; }
		glm::vec2 GetFormationPos() const { return m_FormationPos; }
		glm::vec2 GetPlayerPos() const { return m_Player->GetComponent<Transform>()->GetWorldPosition(); }
		EnemyType GetType() const { return m_Type; }

	private:
		GameObject* m_Player;
		EnemyType m_Type{};
		glm::vec2 m_FormationPos{};
		bool m_ShotOnce{};
		bool m_Flying{false};
		bool m_BeamAttack{ false };
		bool m_IsDead{ false };
		float m_SourceRectX{};
		float m_SourceRectY{};
		float m_Time{};
		float m_Size{};
	};
}