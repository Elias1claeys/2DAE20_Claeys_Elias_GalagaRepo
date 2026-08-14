#pragma once

#include "Core/GameObject.h"
#include "Event/Observer.h"
#include "Components/Text.h"

namespace dae
{
	class ScoreObserver : public Observer
	{
	public:

		ScoreObserver(Text* score);
		virtual ~ScoreObserver() = default;
		ScoreObserver(const ScoreObserver& other) = delete;
		ScoreObserver(ScoreObserver&& other) = delete;
		ScoreObserver& operator=(const ScoreObserver& other) = delete;
		ScoreObserver& operator=(ScoreObserver&& other) = delete;

		void OnNotify(GameObject* entity, const Event& event) override;

	private:
		Text* m_Text{};
		int m_Score{};
	};
}