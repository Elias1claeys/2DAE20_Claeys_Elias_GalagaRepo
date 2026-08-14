#pragma once
#include "Core/GameObject.h"

namespace dae
{
	class HealthDisplay : public Component
	{
	public:
		HealthDisplay(GameObject* owner);
		virtual ~HealthDisplay() = default;
		HealthDisplay(const HealthDisplay& other) = delete;
		HealthDisplay(HealthDisplay&& other) = delete;
		HealthDisplay& operator=(const HealthDisplay& other) = delete;
		HealthDisplay& operator=(HealthDisplay&& other) = delete;

		void DoDamage();

	private:
		int m_Health = 3;
		std::vector<std::unique_ptr<GameObject>> m_HealthDisplay;
	};
}