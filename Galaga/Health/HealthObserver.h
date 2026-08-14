#pragma once
#include "Event/Observer.h"
#include "HealthDisplay.h"

namespace dae
{
	class HealthObserver final : public Observer
	{

	public:
		HealthObserver(HealthDisplay* health);
		virtual ~HealthObserver() = default;
		HealthObserver(const HealthObserver& other) = delete;
		HealthObserver(HealthObserver&& other) = delete;
		HealthObserver& operator=(const HealthObserver& other) = delete;
		HealthObserver& operator=(HealthObserver&& other) = delete;

		void OnNotify(GameObject* gameObject, const Event& event) override;

	private:
		HealthDisplay* m_HealthDisplay{};
		int m_Health{ 4 };
	};
}